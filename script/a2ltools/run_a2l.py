import subprocess
import os


def log_output(process, log_callback=None):
    """实时输出子进程日志"""
    for line in process.stdout:
        if log_callback:
            log_callback(line)
        else:
            print(line, end='')


def run_a2l_merge(files, output, log_callback=None):
    """
    调用 a2ltool.exe 合并多个 A2L 文件
    示例：
        a2ltool.exe file1.a2l --merge file2.a2l --merge file3.a2l --output merged.a2l
    """
    exe_path = os.path.abspath(os.path.join("Lib", "a2ltool.exe"))
    cmd = [exe_path, files[0]]

    for f in files[1:]:
        cmd += ["--merge", f]
    cmd += ["--output", output]

    if log_callback:
        log_callback(f"执行命令: {' '.join(cmd)}\n")

    try:
        process = subprocess.Popen(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding='utf-8',
            bufsize=1
        )

        log_output(process, log_callback)
        process.wait()

        if process.returncode == 0:
            msg = f"\n✅ 合并完成，输出文件: {output}\n"
        else:
            msg = f"\n❌ 合并失败，退出码: {process.returncode}\n"

        if log_callback:
            log_callback(msg)
        else:
            print(msg)

    except Exception as e:
        err_msg = f"\n⚠️ 执行错误: {e}\n"
        if log_callback:
            log_callback(err_msg)
        else:
            print(err_msg)


def run_a2l_update(a2l_file, elf_file, output, update_mode="PRESERVE", log_callback=None):
    """
    调用 a2ltool.exe 执行更新操作
    示例：
        a2ltool.exe input.a2l --elffile input.elf --update --update-mode PRESERVE --output updated.a2l

    :param a2l_file: 输入的 A2L 文件
    :param elf_file: ELF 文件
    :param output: 输出的更新后文件
    :param update_mode: 更新模式（默认 PRESERVE，可改为 REPLACE、MERGE 等）
    :param log_callback: 日志输出函数
    """
    exe_path = os.path.abspath(os.path.join("Lib", "a2ltool.exe"))
    cmd = [
        exe_path,
        a2l_file,
        "--elffile", elf_file,
        "--update",
        "--update-mode", update_mode,
        "--output", output
    ]

    if log_callback:
        log_callback(f"执行命令: {' '.join(cmd)}\n")

    try:
        process = subprocess.Popen(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            encoding='utf-8',
            bufsize=1
        )

        log_output(process, log_callback)
        process.wait()

        if process.returncode == 0:
            msg = f"\n✅ 更新完成，输出文件: {output}\n"
        else:
            msg = f"\n❌ 更新失败，退出码: {process.returncode}\n"

        if log_callback:
            log_callback(msg)
        else:
            print(msg)

    except Exception as e:
        err_msg = f"\n⚠️ 执行错误: {e}\n"
        if log_callback:
            log_callback(err_msg)
        else:
            print(err_msg)
