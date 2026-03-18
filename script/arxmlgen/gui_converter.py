#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Excel ↔ ARXML 双向转换工具 GUI
支持：
1. Excel 转换为 ARXML
2. ARXML 转换为 Excel
"""

import os
import sys
import tkinter as tk
from tkinter import ttk, filedialog, messagebox, scrolledtext
import threading
from datetime import datetime

# 导入现有的转换模块
try:
    from excel2arxml import SwcTaskArxmlGenerator
except ImportError:
    print("警告：excel2arxml.py 模块导入失败，请确保文件存在")
    SwcTaskArxmlGenerator = None

try:
    import arxml2excel
except ImportError:
    print("警告：arxml2excel.py 模块导入失败，请确保文件存在")
    arxml2excel = None


class ConverterGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Excel ↔ ARXML 双向转换工具")
        self.root.geometry("900x700")
        
        # 移除窗口边框，实现扁平化
        self.root.overrideredirect(False)  # 设置为 True 可以完全移除边框，但这里保留最小化/关闭按钮
        
        # 初始化变量
        self.excel_file = tk.StringVar()
        self.arxml_file = tk.StringVar()
        self.conversion_type = tk.StringVar(value="excel_to_arxml")
        
        # 设置样式
        self.setup_styles()
        
        # 创建主界面
        self.create_widgets()
        
        # 日志区域
        self.create_log_area()
        
        # 状态栏
        self.create_status_bar()
        
    def setup_styles(self):
        """设置界面样式"""
        style = ttk.Style()
        style.theme_use('clam')
        
        # 配置主窗口颜色 - 使用现代扁平化配色
        self.root.configure(bg='#f8f9fa')
        
        # 自定义样式
        style.configure('Title.TLabel', 
                       font=('Segoe UI', 18, 'bold'),
                       background='#f8f9fa',
                       foreground='#2c3e50')
        
        style.configure('Flat.TFrame',
                       background='#f8f9fa')
        
        style.configure('Card.TLabelframe',
                       background='#ffffff',
                       relief='flat',
                       borderwidth=0)
        
        style.configure('Card.TLabelframe.Label',
                       font=('Segoe UI', 11, 'bold'),
                       background='#ffffff',
                       foreground='#2c3e50')
        
        style.configure('Primary.TButton',
                       font=('Segoe UI', 10, 'bold'),
                       background='#3498db',
                       foreground='white',
                       borderwidth=0,
                       focusthickness=0,
                       focuscolor='none')
        
        style.map('Primary.TButton',
                 background=[('active', '#2980b9')])
        
        style.configure('Secondary.TButton',
                       font=('Segoe UI', 10),
                       background='#95a5a6',
                       foreground='white',
                       borderwidth=0)
        
        style.map('Secondary.TButton',
                 background=[('active', '#7f8c8d')])
        
        style.configure('Radio.TRadiobutton',
                       font=('Segoe UI', 10),
                       background='#ffffff',
                       foreground='#2c3e50')
        
        style.configure('Entry.TEntry',
                       fieldbackground='#ffffff',
                       borderwidth=1,
                       relief='flat')
        
        style.configure('Status.TLabel',
                       font=('Segoe UI', 9),
                       background='#34495e',
                       foreground='#ecf0f1',
                       relief='flat')
        
    def create_widgets(self):
        """创建主界面控件"""
        # 主框架 - 使用扁平化样式
        main_frame = ttk.Frame(self.root, style='Flat.TFrame', padding="30")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # 标题 - 使用自定义样式
        title_label = ttk.Label(main_frame, text="Excel ↔ ARXML 双向转换工具", 
                               style='Title.TLabel')
        title_label.grid(row=0, column=0, columnspan=3, pady=(0, 30))
        
        # 转换类型选择 - 使用卡片样式
        type_frame = ttk.LabelFrame(main_frame, text="转换类型", 
                                   style='Card.TLabelframe', padding="15")
        type_frame.grid(row=1, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=(0, 20))
        
        ttk.Radiobutton(type_frame, text="Excel → ARXML", 
                       variable=self.conversion_type, 
                       value="excel_to_arxml",
                       style='Radio.TRadiobutton',
                       command=self.on_conversion_type_changed).grid(row=0, column=0, padx=15)
        
        ttk.Radiobutton(type_frame, text="ARXML → Excel", 
                       variable=self.conversion_type, 
                       value="arxml_to_excel",
                       style='Radio.TRadiobutton',
                       command=self.on_conversion_type_changed).grid(row=0, column=1, padx=15)
        
        # Excel 文件选择 - 使用卡片样式
        excel_frame = ttk.LabelFrame(main_frame, text="Excel 文件", 
                                    style='Card.TLabelframe', padding="15")
        excel_frame.grid(row=2, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=(0, 15))
        
        ttk.Label(excel_frame, text="Excel 文件路径:", 
                 style='Card.TLabelframe.Label').grid(row=0, column=0, sticky=tk.W)
        
        excel_entry = ttk.Entry(excel_frame, textvariable=self.excel_file, 
                               width=55, style='Entry.TEntry')
        excel_entry.grid(row=0, column=1, padx=(10, 5))
        
        ttk.Button(excel_frame, text="浏览", 
                  command=self.browse_excel_file,
                  style='Secondary.TButton').grid(row=0, column=2)
        
        # ARXML 文件选择 - 使用卡片样式
        arxml_frame = ttk.LabelFrame(main_frame, text="ARXML 文件", 
                                    style='Card.TLabelframe', padding="15")
        arxml_frame.grid(row=3, column=0, columnspan=3, sticky=(tk.W, tk.E), pady=(0, 15))
        
        ttk.Label(arxml_frame, text="ARXML 文件路径:", 
                 style='Card.TLabelframe.Label').grid(row=0, column=0, sticky=tk.W)
        
        arxml_entry = ttk.Entry(arxml_frame, textvariable=self.arxml_file, 
                               width=55, style='Entry.TEntry')
        arxml_entry.grid(row=0, column=1, padx=(10, 5))
        
        ttk.Button(arxml_frame, text="浏览", 
                  command=self.browse_arxml_file,
                  style='Secondary.TButton').grid(row=0, column=2)
        
        # 转换按钮区域
        button_frame = ttk.Frame(main_frame, style='Flat.TFrame')
        button_frame.grid(row=4, column=0, columnspan=3, pady=30)
        
        self.convert_button = ttk.Button(button_frame, text="开始转换", 
                                        command=self.start_conversion,
                                        style='Primary.TButton',
                                        width=15)
        self.convert_button.grid(row=0, column=0, padx=10)
        
        ttk.Button(button_frame, text="清空日志", 
                  command=self.clear_log,
                  style='Secondary.TButton',
                  width=10).grid(row=0, column=1, padx=10)
        
        ttk.Button(button_frame, text="退出", 
                  command=self.root.quit,
                  style='Secondary.TButton',
                  width=10).grid(row=0, column=2, padx=10)
        
        # 配置网格权重
        main_frame.columnconfigure(1, weight=1)
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        
    def create_log_area(self):
        """创建日志显示区域"""
        # 为日志区域创建自定义样式
        style = ttk.Style()
        style.configure('Log.TLabelframe',
                       background='#ffffff',
                       relief='flat',
                       borderwidth=0)
        
        style.configure('Log.TLabelframe.Label',
                       font=('Segoe UI', 11, 'bold'),
                       background='#ffffff',
                       foreground='#2c3e50')
        
        # 日志框架 - 使用卡片样式
        log_frame = ttk.LabelFrame(self.root, text="转换日志", 
                                  style='Log.TLabelframe', padding="15")
        log_frame.grid(row=1, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), 
                      padx=30, pady=(0, 20))
        
        # 创建自定义样式的文本框
        self.log_text = scrolledtext.ScrolledText(
            log_frame, 
            height=15, 
            width=85,
            bg='#f8f9fa',  # 背景色
            fg='#2c3e50',  # 文字颜色
            font=('Consolas', 9),  # 等宽字体
            relief='flat',  # 扁平边框
            borderwidth=1,
            highlightthickness=1,
            highlightbackground='#e0e0e0',  # 边框颜色
            highlightcolor='#3498db'  # 焦点边框颜色
        )
        self.log_text.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # 配置网格权重
        self.root.rowconfigure(1, weight=1)
        self.root.columnconfigure(0, weight=1)
        log_frame.columnconfigure(0, weight=1)
        log_frame.rowconfigure(0, weight=1)
        
    def create_status_bar(self):
        """创建状态栏"""
        self.status_var = tk.StringVar(value="就绪")
        status_bar = ttk.Label(self.root, textvariable=self.status_var, 
                              relief=tk.SUNKEN, anchor=tk.W)
        status_bar.grid(row=2, column=0, sticky=(tk.W, tk.E))
        
    def on_conversion_type_changed(self):
        """转换类型改变时的处理"""
        conversion_type = self.conversion_type.get()
        if conversion_type == "excel_to_arxml":
            self.status_var.set("已选择：Excel → ARXML 转换")
        else:
            self.status_var.set("已选择：ARXML → Excel 转换")
            
    def browse_excel_file(self):
        """浏览 Excel 文件"""
        filetypes = [
            ("Excel 文件", "*.xlsx *.xls"),
            ("所有文件", "*.*")
        ]
        
        filename = filedialog.askopenfilename(
            title="选择 Excel 文件",
            filetypes=filetypes
        )
        
        if filename:
            self.excel_file.set(filename)
            self.log_message(f"已选择 Excel 文件: {filename}")
            
            # 自动生成 ARXML 文件名
            if self.conversion_type.get() == "excel_to_arxml":
                base_name = os.path.splitext(filename)[0]
                arxml_name = f"{base_name}_output.arxml"
                self.arxml_file.set(arxml_name)
    
    def browse_arxml_file(self):
        """浏览 ARXML 文件"""
        filetypes = [
            ("ARXML 文件", "*.arxml"),
            ("所有文件", "*.*")
        ]
        
        filename = filedialog.askopenfilename(
            title="选择 ARXML 文件",
            filetypes=filetypes
        )
        
        if filename:
            self.arxml_file.set(filename)
            self.log_message(f"已选择 ARXML 文件: {filename}")
            
            # 自动生成 Excel 文件名
            if self.conversion_type.get() == "arxml_to_excel":
                base_name = os.path.splitext(filename)[0]
                excel_name = f"{base_name}_output.xlsx"
                self.excel_file.set(excel_name)
    
    def log_message(self, message):
        """添加日志消息"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        log_entry = f"[{timestamp}] {message}\n"
        
        self.log_text.insert(tk.END, log_entry)
        self.log_text.see(tk.END)  # 自动滚动到底部
        self.root.update_idletasks()
    
    def clear_log(self):
        """清空日志"""
        self.log_text.delete(1.0, tk.END)
        self.log_message("日志已清空")
    
    def start_conversion(self):
        """开始转换"""
        conversion_type = self.conversion_type.get()
        
        if conversion_type == "excel_to_arxml":
            excel_file = self.excel_file.get()
            arxml_file = self.arxml_file.get()
            
            if not excel_file:
                messagebox.showerror("错误", "请选择 Excel 文件")
                return
                
            if not arxml_file:
                messagebox.showerror("错误", "请指定 ARXML 输出文件")
                return
                
            # 检查 Excel 文件是否存在
            if not os.path.exists(excel_file):
                messagebox.showerror("错误", f"Excel 文件不存在: {excel_file}")
                return
                
            self.log_message(f"开始 Excel → ARXML 转换")
            self.log_message(f"输入文件: {excel_file}")
            self.log_message(f"输出文件: {arxml_file}")
            
            # 在新线程中执行转换
            thread = threading.Thread(
                target=self.convert_excel_to_arxml,
                args=(excel_file, arxml_file)
            )
            thread.daemon = True
            thread.start()
            
        else:  # arxml_to_excel
            arxml_file = self.arxml_file.get()
            excel_file = self.excel_file.get()
            
            if not arxml_file:
                messagebox.showerror("错误", "请选择 ARXML 文件")
                return
                
            if not excel_file:
                messagebox.showerror("错误", "请指定 Excel 输出文件")
                return
                
            # 检查 ARXML 文件是否存在
            if not os.path.exists(arxml_file):
                messagebox.showerror("错误", f"ARXML 文件不存在: {arxml_file}")
                return
                
            self.log_message(f"开始 ARXML → Excel 转换")
            self.log_message(f"输入文件: {arxml_file}")
            self.log_message(f"输出文件: {excel_file}")
            
            # 在新线程中执行转换
            thread = threading.Thread(
                target=self.convert_arxml_to_excel,
                args=(arxml_file, excel_file)
            )
            thread.daemon = True
            thread.start()
    
    def convert_excel_to_arxml(self, excel_file, arxml_file):
        """执行 Excel 到 ARXML 的转换"""
        try:
            self.status_var.set("正在转换 Excel → ARXML...")
            self.convert_button.config(state="disabled")
            
            if SwcTaskArxmlGenerator is None:
                raise ImportError("excel2arxml 模块未找到")
            
            # 执行转换
            generator = SwcTaskArxmlGenerator(excel_file, arxml_file)
            generator.generate()
            
            # 记录成功
            self.log_message("✅ 转换成功！")
            self.log_message(f"生成的 ARXML 文件: {arxml_file}")
            
            # 显示成功消息
            self.root.after(0, lambda: messagebox.showinfo(
                "转换成功", 
                f"Excel 文件已成功转换为 ARXML 文件:\n{arxml_file}"
            ))
            
        except Exception as e:
            error_msg = f"转换失败: {str(e)}"
            self.log_message(f"❌ {error_msg}")
            self.root.after(0, lambda: messagebox.showerror("转换失败", error_msg))
            
        finally:
            self.status_var.set("就绪")
            self.root.after(0, lambda: self.convert_button.config(state="normal"))
    
    def convert_arxml_to_excel(self, arxml_file, excel_file):
        """执行 ARXML 到 Excel 的转换"""
        try:
            self.status_var.set("正在转换 ARXML → Excel...")
            self.convert_button.config(state="disabled")
            
            if arxml2excel is None:
                raise ImportError("arxml2excel 模块未找到")
            
            # 检查 arxml2excel 模块是否有转换函数
            if hasattr(arxml2excel, 'convert_arxml_to_excel'):
                # 调用模块中的转换函数
                arxml2excel.convert_arxml_to_excel(arxml_file, excel_file)
            else:
                # 尝试导入并执行主函数
                import subprocess
                result = subprocess.run(
                    [sys.executable, "arxml2excel.py", arxml_file, excel_file],
                    capture_output=True,
                    text=True
                )
                
                if result.returncode != 0:
                    raise Exception(f"转换失败: {result.stderr}")
            
            # 记录成功
            self.log_message("✅ 转换成功！")
            self.log_message(f"生成的 Excel 文件: {excel_file}")
            
            # 显示成功消息
            self.root.after(0, lambda: messagebox.showinfo(
                "转换成功", 
                f"ARXML 文件已成功转换为 Excel 文件:\n{excel_file}"
            ))
            
        except Exception as e:
            error_msg = f"转换失败: {str(e)}"
            self.log_message(f"❌ {error_msg}")
            self.root.after(0, lambda: messagebox.showerror("转换失败", error_msg))
            
        finally:
            self.status_var.set("就绪")
            self.root.after(0, lambda: self.convert_button.config(state="normal"))


def main():
    """主函数"""
    root = tk.Tk()
    app = ConverterGUI(root)
    
    # 配置窗口关闭事件
    def on_closing():
        if messagebox.askokcancel("退出", "确定要退出程序吗？"):
            root.destroy()
    
    root.protocol("WM_DELETE_WINDOW", on_closing)
    
    # 启动主循环
    root.mainloop()


if __name__ == "__main__":
    main()