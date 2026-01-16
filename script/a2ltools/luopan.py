import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import os
from datetime import datetime
from run_a2l import run_a2l_merge,run_a2l_update
import threading
from A2lCheck import convert_custom_params_inplace,convert_to_title_case_inplace
from time import sleep as timesleep

class A2LToolApp:
    def __init__(self, root):
        self.root = root
        self.root.title("罗盘A2L工具 v1.0")
        self.root.geometry("900x700")
        
        # 设置主题风格
        self.setup_style()
        
        # 创建主框架
        self.main_frame = ttk.Frame(root)
        self.main_frame.pack(fill=tk.BOTH, expand=True, padx=15, pady=5)
        
        # 使用grid布局来控制比例
        self.main_frame.grid_rowconfigure(0, weight=6)  # 页面区域占60%
        self.main_frame.grid_rowconfigure(1, weight=4)  # 日志区域占40%
        self.main_frame.grid_columnconfigure(0, weight=1)
        
        # 创建标签页控件
        self.notebook = ttk.Notebook(self.main_frame)
        self.notebook.grid(row=0, column=0, sticky="nsew", padx=5, pady=5)
        
        # 创建两个页面
        self.create_generate_page()
        self.create_merge_page()
        
        # 创建底部日志区域
        self.create_log_area()
        
    def setup_style(self):
        """设置界面风格"""
        style = ttk.Style()
        style.theme_use('clam')  # 使用clam主题
        
        # 配置样式
        style.configure('Accent.TButton', font=('Arial', 10, 'bold'))
        style.configure('Title.TLabel', font=('Arial', 14, 'bold'))
        style.configure('Subtitle.TLabel', font=('Arial', 11, 'bold'))
        
    def create_log_area(self):
        """创建底部日志输出区域"""
        log_frame = ttk.LabelFrame(self.main_frame, text="操作日志", padding=8)
        log_frame.grid(row=1, column=0, sticky="nsew", padx=5, pady=(5, 0))
        
        # 创建日志文本框和滚动条 - 增加高度
        self.log_text = scrolledtext.ScrolledText(
            log_frame, 
            height=20,  # 增加高度
            wrap=tk.WORD,
            font=('Consolas', 9),
            bg='#f5f5f5',
            fg='#333333'
        )
        self.log_text.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        # 日志控制按钮 - 放在右边，上下排列
        log_buttons_frame = ttk.Frame(log_frame)
        log_buttons_frame.pack(side=tk.RIGHT, fill=tk.Y, pady=5)  # 改为side=tk.RIGHT

        ttk.Button(log_buttons_frame, text="清空日志", 
                command=self.clear_log, width=10).pack(side=tk.TOP, fill=tk.X, padx=5, pady=2)
        ttk.Button(log_buttons_frame, text="保存日志", 
                command=self.save_log, width=10).pack(side=tk.TOP, fill=tk.X, padx=5, pady=2)
        
        self.log("A2L工具启动成功")
        
    def log(self, message, level="INFO"):
        """添加日志消息"""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_entry = f"[{timestamp}] [{level}] {message}\n"
        
        self.log_text.insert(tk.END, log_entry)
        self.log_text.see(tk.END)  # 自动滚动到底部
        
        # 根据日志级别设置颜色
        if level == "ERROR":
            self.log_text.tag_add("error", "end-2l", "end-1l")
            self.log_text.tag_config("error", foreground="red")
        elif level == "SUCCESS":
            self.log_text.tag_add("success", "end-2l", "end-1l")
            self.log_text.tag_config("success", foreground="green")
        
    def clear_log(self):
        """清空日志"""
        self.log_text.delete(1.0, tk.END)
        self.log("日志已清空")
        
    def save_log(self):
        """保存日志到文件"""
        filename = filedialog.asksaveasfilename(
            title="保存日志文件",
            defaultextension=".log",
            filetypes=[("日志文件", "*.log"), ("文本文件", "*.txt"), ("所有文件", "*.*")]
        )
        if filename:
            try:
                with open(filename, 'w', encoding='utf-8') as f:
                    f.write(self.log_text.get(1.0, tk.END))
                self.log(f"日志已保存到: {filename}", "SUCCESS")
            except Exception as e:
                self.log(f"保存日志失败: {str(e)}", "ERROR")
                
    def create_generate_page(self):
        """创建生成A2L页面"""
        self.generate_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.generate_frame, text="📄 生成A2L")
        
        # 主容器 - 分为左右两部分
        main_container = ttk.Frame(self.generate_frame)
        main_container.pack(fill=tk.BOTH, expand=True, padx=10, pady=10)
        
        # 左侧配置区域
        config_frame = ttk.Frame(main_container)
        config_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(0, 10))

        # A2L头文件选择
        input_frame = ttk.LabelFrame(config_frame, text="选择头文件", padding=1)
        input_frame.pack(fill=tk.X, pady=2)
        
        file_entry_frame = ttk.Frame(input_frame)
        file_entry_frame.pack(fill=tk.X, pady=2)
        
        self.head_file_var = tk.StringVar()
        
        # 获取 A2lHead 文件夹下的文件列表
        self.a2l_head_dir = "A2lHead"
        self.file_list = self.get_a2l_files()
        
        # 下拉框替代原来的 Entry
        self.file_combobox = ttk.Combobox(file_entry_frame, 
                                          textvariable=self.head_file_var,
                                          values=self.file_list,
                                          font=('Arial', 10))
        self.file_combobox.pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        ttk.Button(file_entry_frame, text="清空", 
                   command=lambda: self.head_file_var.set(""), width=6).pack(side=tk.LEFT, padx=(2, 0))
        
        # 输入A2L文件选择
        input_frame = ttk.LabelFrame(config_frame, text="输入A2L文件", padding=1)
        input_frame.pack(fill=tk.X, pady=2)
        
        file_entry_frame = ttk.Frame(input_frame)
        file_entry_frame.pack(fill=tk.X, pady=2)
        
        self.a2l_file_var = tk.StringVar()
        file_entry = ttk.Entry(file_entry_frame, textvariable=self.a2l_file_var, font=('Arial', 10))
        file_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        ttk.Button(file_entry_frame, text="浏览文件", 
                  command=self.browse_a2l_file, width=8).pack(side=tk.LEFT, padx=(5, 0))
        ttk.Button(file_entry_frame, text="清空", 
                  command=lambda: self.a2l_file_var.set(""), width=6).pack(side=tk.LEFT, padx=(2, 0))

        # 输入ELF文件选择
        input_frame = ttk.LabelFrame(config_frame, text="输入ELF", padding=1)
        input_frame.pack(fill=tk.X, pady=2)
        
        file_entry_frame = ttk.Frame(input_frame)
        file_entry_frame.pack(fill=tk.X, pady=2)
        
        self.elf_file_var = tk.StringVar()
        file_entry = ttk.Entry(file_entry_frame, textvariable=self.elf_file_var, font=('Arial', 10))
        file_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        ttk.Button(file_entry_frame, text="浏览文件", 
                  command=self.browse_elf_file, width=8).pack(side=tk.LEFT, padx=(5, 0))
        ttk.Button(file_entry_frame, text="清空", 
                  command=lambda: self.elf_file_var.set(""), width=6).pack(side=tk.LEFT, padx=(2, 0))

        # 输出文件选择
        output_frame = ttk.LabelFrame(config_frame, text="输出设置", padding=1)
        output_frame.pack(fill=tk.X, pady=2)
        file_entry_frame = ttk.Frame(output_frame)
        file_entry_frame.pack(fill=tk.X, pady=2)

        self.output_file_var = tk.StringVar()
        file_entry = ttk.Entry(file_entry_frame, textvariable=self.output_file_var, font=('Arial', 10))
        file_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)

        ttk.Button(file_entry_frame, text="浏览文件", 
                  command=self.browse_output_file, width=8).pack(side=tk.LEFT, padx=(5, 0))
        ttk.Button(file_entry_frame, text="清空", 
                  command=lambda: self.output_file_var.set(""), width=6).pack(side=tk.LEFT, padx=(2, 0))
        

        
        # 右侧按钮区域
        button_frame = ttk.LabelFrame(main_container, text="操作", padding=15)
        button_frame.pack(side=tk.RIGHT, fill=tk.Y, padx=(10, 0))
        
        # 操作按钮
        ttk.Button(button_frame, text="生成INCA A2L", 
                  command=self.generate_INCA_a2l, 
                  style="Accent.TButton",
                  width=15).pack(pady=5)
        ttk.Button(button_frame, text="生成APE A2L", 
                  command=self.generate_ape_a2l, 
                  style="Accent.TButton",
                  width=15).pack(pady=5)
        ttk.Button(button_frame, text="更新A2L地址", 
                  command=self.update_addresses, 
                  style="Accent.TButton",
                  width=15).pack(pady=5)

        ttk.Button(button_frame, text="验证输入", 
                  command=self.validate_generate_input,
                  width=15).pack(pady=5)
        
        ttk.Button(button_frame, text="重置表单", 
                  command=self.reset_generate_form,
                  width=15).pack(pady=5)
        
    def create_merge_page(self):
        """创建合并A2L页面"""
        self.merge_frame = ttk.Frame(self.notebook)
        self.notebook.add(self.merge_frame, text="🔗 合并A2L")
        
        # 主容器
        main_container = ttk.Frame(self.merge_frame)
        main_container.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)
        
        # 左侧配置区域
        config_frame = ttk.Frame(main_container)
        config_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(0, 5))
        
        # 文件列表
        list_frame = ttk.LabelFrame(config_frame, text="待合并文件列表", padding=6)
        list_frame.pack(fill=tk.BOTH, expand=True, pady=2)
        #list_frame.grid(row=0, column=0, sticky="nsew", pady=2)
        
        # 文件列表和滚动条
        list_container = ttk.Frame(list_frame)
        list_container.pack(side=tk.LEFT,fill=tk.BOTH, expand=True)

        list_container.grid_rowconfigure(0, weight=1)
        list_container.grid_columnconfigure(0, weight=1)
        list_container.grid_columnconfigure(1, weight=0)

        self.file_listbox = tk.Listbox(list_container, height=5, font=('Arial', 8))
        scrollbar = ttk.Scrollbar(list_container, orient=tk.VERTICAL, command=self.file_listbox.yview)
        self.file_listbox.configure(yscrollcommand=scrollbar.set)
        
        self.file_listbox.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
        
        # 文件操作按钮
        file_buttons_frame = ttk.Frame(list_frame)
        file_buttons_frame.pack(side=tk.RIGHT,fill=tk.X, pady=(2, 0))
        
        ttk.Button(file_buttons_frame, text="添加文件", 
                  command=self.add_merge_files).pack(side=tk.TOP, padx=5,pady=4)
        ttk.Button(file_buttons_frame, text="移除选中", 
                  command=self.remove_selected_files).pack(side=tk.TOP, padx=5,pady=4)
        ttk.Button(file_buttons_frame, text="清空列表", 
                  command=self.clear_file_list).pack(side=tk.TOP, padx=5,pady=4)
        
        # 输出设置
        output_frame = ttk.LabelFrame(config_frame, text="合并输出", padding=5)
        output_frame.pack(fill=tk.X, pady=2)
        
        output_entry_frame = ttk.Frame(output_frame)
        output_entry_frame.pack(fill=tk.X, pady=5)
        
        self.merge_output_var = tk.StringVar()
        output_entry = ttk.Entry(output_entry_frame, textvariable=self.merge_output_var, font=('Arial', 10))
        output_entry.pack(side=tk.LEFT, fill=tk.X, expand=True)
        
        ttk.Button(output_entry_frame, text="浏览", 
                  command=self.browse_merge_output, width=8).pack(side=tk.LEFT, padx=(5, 0))
        ttk.Button(output_entry_frame, text="清空", 
                  command=lambda: self.merge_output_var.set(""), width=6).pack(side=tk.LEFT, padx=(2, 0))
        
        # 右侧按钮区域
        button_frame = ttk.LabelFrame(main_container, text="操作", padding=15)
        button_frame.pack(side=tk.RIGHT, fill=tk.Y, padx=(10, 0))
        
        # 操作按钮
        ttk.Button(button_frame, text="开始合并", 
                  command=self.merge_a2l_files, 
                  style="Accent.TButton",
                  width=15).pack(pady=5)
        
        ttk.Button(button_frame, text="验证文件", 
                  command=self.validate_merge_files,
                  width=15).pack(pady=5)
        
        ttk.Button(button_frame, text="重新排序", 
                  command=self.sort_file_list,
                  width=15).pack(pady=5)
        
        ttk.Button(button_frame, text="重置", 
                  command=self.reset_merge_form,
                  width=15).pack(pady=5)
        
    def get_a2l_files(self):
        """返回A2lHead目录下的文件列表"""
        if not os.path.exists(self.a2l_head_dir):
            return []
        # 只获取文件名，不包括路径
        return [f for f in os.listdir(self.a2l_head_dir) if os.path.isfile(os.path.join(self.a2l_head_dir, f))]
    
    # 文件浏览方法（保持不变）
    def browse_a2l_file(self):
        filename = filedialog.askopenfilename(
            title="选择A2L文件",
            filetypes=[("A2L文件", "*.a2l"), ("所有文件", "*.*")]
        )
        if filename:
            self.a2l_file_var.set(filename)
            self.log(f"选择A2L文件: {filename}")
            self.auto_generate_output_name()

    def browse_elf_file(self):
        filename = filedialog.askopenfilename(
            title="选择ELF文件",
            filetypes=[("ELF文件", "*.elf"), ("所有文件", "*.*")]
        )
        if filename:
            self.elf_file_var.set(filename)
            self.log(f"选择ELF文件: {filename}")
            self.auto_generate_output_name()

    def browse_output_file(self):
        filename = filedialog.asksaveasfilename(
            title="选择输出文件",
            defaultextension=".a2l",
            filetypes=[("A2L文件", "*.a2l"), ("所有文件", "*.*")]
        )
        if filename:
            self.output_file_var.set(filename)
            self.log(f"选择输出文件: {filename}")

    def browse_merge_output(self):
        filename = filedialog.asksaveasfilename(
            title="保存合并文件",
            defaultextension=".a2l",
            filetypes=[("A2L文件", "*.a2l"), ("所有文件", "*.*")]
        )
        if filename:
            self.merge_output_var.set(filename)
            self.log(f"设置合并输出文件: {filename}")    

    def browse_updated_output(self):
        filename = filedialog.asksaveasfilename(
            title="保存更新后的文件",
            defaultextension=".a2l",
            filetypes=[("A2L文件", "*.a2l"), ("所有文件", "*.*")]
        )
        if filename:
            self.output_file_var.set(filename)
            self.log(f"设置更新输出文件: {filename}")
    
    # 文件列表操作方法（保持不变）
    def add_merge_files(self):
        files = filedialog.askopenfilenames(
            title="选择要合并的A2L文件",
            filetypes=[("A2L文件", "*.a2l"), ("所有文件", "*.*")]
        )
        for file in files:
            self.file_listbox.insert(tk.END, file)
            self.log(f"添加合并文件: {file}")

            if not self.merge_output_var.get():
                # 组合生成输出文件名
                output_name = f"merge_output.a2l"

                # 如果输入文件有目录，使用相同的目录
                file_dir = os.path.dirname(file)
                if file_dir:
                    output_path = os.path.join(file_dir, output_name)
                else:
                    output_path = output_name
                    
                self.merge_output_var.set(output_path)
                self.log(f"自动生成输出文件名: {output_path}")
    
    def remove_selected_files(self):
        selected = self.file_listbox.curselection()
        for index in selected[::-1]:
            file = self.file_listbox.get(index)
            self.file_listbox.delete(index)
            self.log(f"移除文件: {file}")
    
    def clear_file_list(self):
        count = self.file_listbox.size()
        self.file_listbox.delete(0, tk.END)
        self.log(f"清空文件列表，共移除 {count} 个文件")
    
    # 新增辅助方法
    def validate_generate_input(self):
        """验证生成页面的输入"""
        if not self.head_file_var.get():
            self.log("错误：请选择头文件", "ERROR")
            return False
        if not self.a2l_file_var.get():
            self.log("错误：请选择A2L文件", "ERROR")
            return False
        if not self.elf_file_var.get():
            self.log("错误：请选择ELF文件", "ERROR")
            return False
        if not self.output_file_var.get():
            self.log("错误：请选择输出文件", "ERROR")
            return False
        self.log("输入验证通过", "SUCCESS")
        return True

    def validate_update_files(self):
        """验证更新页面的输入"""
        if not self.a2l_file_var.get():
            self.log("错误：请选择A2L文件", "ERROR")
            return False
        if not self.elf_file_var.get():
            self.log("错误：请选择ELF文件", "ERROR")
            return False
        if not self.output_file_var.get():
            self.log("错误：请指定输出文件", "ERROR")
            return False
        self.log("文件验证通过", "SUCCESS")
        return True

    def validate_merge_files(self):
        """验证合并页面的输入"""
        if self.file_listbox.size() < 2:
            self.log("错误：请至少选择两个文件进行合并", "ERROR")
            return False
        if not self.merge_output_var.get():
            self.log("错误：请指定输出文件", "ERROR")
            return False
        self.log("文件验证通过", "SUCCESS")
        return True
    
    
    def reset_generate_form(self):
        """重置生成页面表单"""
        self.head_file_var.set("")
        self.a2l_file_var.set("")
        self.elf_file_var.set("")
        self.output_file_var.set("")
        self.log("生成页面表单已重置")
    
    def reset_merge_form(self):
        """重置合并页面表单"""
        self.file_listbox.delete(0, tk.END)
        self.merge_output_var.set("")
        self.log("合并页面表单已重置")
    
    def sort_file_list(self):
        """对文件列表进行排序"""
        files = [self.file_listbox.get(i) for i in range(self.file_listbox.size())]
        files.sort()
        self.file_listbox.delete(0, tk.END)
        for file in files:
            self.file_listbox.insert(tk.END, file)
        self.log("文件列表已按名称排序")
    
    def preview_changes(self):
        """预览地址更新更改"""
        self.log("预览功能开发中...", "INFO")

    def auto_generate_output_name(self, *args):
        """自动生成输出文件名：输入文件+ELF文件组合"""
        a2l_file = self.a2l_file_var.get()
        elf_file = self.elf_file_var.get()
        
        if a2l_file and elf_file:
            # 获取输入文件和ELF文件的基本名（不含扩展名）
            a2l_base = os.path.splitext(os.path.basename(a2l_file))[0]
            elf_base = os.path.splitext(os.path.basename(elf_file))[0]
            
            # 组合生成输出文件名
            output_name = f"{a2l_base}_{elf_base}.a2l"
            
            # 如果输入文件有目录，使用相同的目录
            a2l_dir = os.path.dirname(a2l_file)
            if a2l_dir:
                output_path = os.path.join(a2l_dir, output_name)
            else:
                output_path = output_name
            
            # 规范化路径，统一分隔符
            output_path = os.path.normpath(output_path)
            self.output_file_var.set(output_path)
            self.log(f"自动生成输出文件名: {output_path}")

    def generate_INCA_a2l(self):
        self.generate_a2l("INCA")

    def generate_ape_a2l(self):
        self.generate_a2l("APE")
        

    # 功能方法（这里需要根据实际需求实现具体功能）
    def generate_a2l(self,Type: str):
        """生成A2L文件"""
        if not self.validate_generate_input():
            return
        head_file = os.path.abspath(os.path.join("A2lHead", self.head_file_var.get()))
        a2l_file = self.a2l_file_var.get()
        elf_file = self.elf_file_var.get()
        merge_file = r"merge_output.a2l"
        output_file = self.output_file_var.get()
        
        self.log("开始生成A2L文件...")
        
        try:
            # 这里添加实际的生成A2L逻辑
            # 模拟处理过程
            self.log(f"使用头文件: {head_file}")
            self.log(f"处理A2L文件: {os.path.basename(a2l_file)}")
            self.log(f"映射文件: {os.path.basename(elf_file)}")
            update_mode = "PRESERVE"  # 从界面选择或默认

            self.log(f"开始更新 A2L 文件，模式：{update_mode}\n")
            run_a2l_merge(
                [head_file, a2l_file],
                merge_file,
                self.log
            )


            run_a2l_update(merge_file, elf_file, output_file, update_mode, self.log)
            # 模拟处理时间
            self.log("A2L文件生成中...")

            if merge_file and os.path.exists(merge_file):
                try:
                    os.remove(merge_file)
                    print(f"已删除文件: {merge_file}")
                    self.log("文件已删除: " + merge_file)
                except Exception as e:
                    print(f"删除失败: {e}")
                    self.log("删除文件失败: " + str(e))

            message = f"A2L文件生成成功！\n源文件: {a2l_file}\n输出文件: {output_file}"
            if Type=="APE":
                convert_to_title_case_inplace(output_file)
            elif Type=="INCA":
                convert_custom_params_inplace(output_file)
            self.log(message, "SUCCESS")
            
        except Exception as e:
            self.log(f"生成A2L文件失败: {str(e)}", "ERROR")
    
    def merge_a2l_files(self):
        """合并A2L文件"""
        if not self.validate_merge_files():
            return
            
        file_count = self.file_listbox.size()
        output_file = self.merge_output_var.get()
        
        self.log(f"开始合并 {file_count} 个A2L文件...")
        
        try:
            files = [self.file_listbox.get(i) for i in range(file_count)]

            self.log("开始合并 A2L 文件...\n")

            # 使用线程避免 GUI 卡死
            threading.Thread(
                target=run_a2l_merge,
                args=(files, output_file, self.log),
                daemon=True
            ).start()
                    
        except Exception as e:
            self.log(f"合并A2L文件失败: {str(e)}", "ERROR")
    
    def update_addresses(self):
        """更新地址"""
        if not self.validate_update_files():
            return

        a2l_file = self.a2l_file_var.get()
        elf_file = self.elf_file_var.get()
        output_file = self.output_file_var.get()
        
        self.log("开始更新A2L文件地址...")
        
        try:
            self.log(f"A2L文件: {os.path.basename(a2l_file)}")
            self.log(f"映射文件: {os.path.basename(elf_file)}")
            update_mode = "PRESERVE"  # 从界面选择或默认

            self.log(f"开始更新 A2L 文件，模式：{update_mode}\n")

            threading.Thread(
                target=run_a2l_update,
                args=(a2l_file, elf_file, output_file, update_mode, self.log),
                daemon=True
            ).start()
            self.log("地址更新中...")
            
            message = f"地址更新成功！\nA2L文件: {a2l_file}\n映射文件: {a2l_file}\n输出文件: {output_file}"
            self.log(message, "SUCCESS")
            
        except Exception as e:
            self.log(f"更新地址失败: {str(e)}", "ERROR")

def main():
    root = tk.Tk()
    app = A2LToolApp(root)
    root.mainloop()

if __name__ == "__main__":
    main()