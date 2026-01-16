import re

def convert_custom_params_inplace(file_path, target_params=None):
    """
    只修改指定的参数列表
    """
    if target_params is None:
        target_params = ['Protocol_Layer', 'Daq']
    
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 创建正则表达式模式，匹配指定的参数
    params_pattern = '|'.join(re.escape(param) for param in target_params)
    pattern = rf'(/begin\s+|\bend\s+)({params_pattern})'
    
    def to_upper(match):
        prefix = match.group(1)
        param_name = match.group(2)
        
        # 检查参数是否在目标列表中（不区分大小写）
        if param_name.lower() in [p.lower() for p in target_params]:
            return prefix + param_name.upper()
        else:
            return match.group(0)
    
    converted_content = re.sub(pattern, to_upper, content, flags=re.IGNORECASE)
    
    if converted_content != content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(converted_content)
        print(f"文件已更新: {file_path}")
        return True
    else:
        print(f"文件无需修改: {file_path}")
        return False
    


def convert_to_title_case_inplace(file_path, target_params=None):
    """
    将指定参数转换为首字母大写，其他保持不变
    """
    if target_params is None:
        target_params = ['SEGMENT']
    
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 创建正则表达式模式，匹配指定的参数
    params_pattern = '|'.join(re.escape(param) for param in target_params)
    pattern = rf'(/begin\s+|\bend\s+)({params_pattern})'
    
    def to_title_case(match):
        prefix = match.group(1)
        param_name = match.group(2)
        
        # 检查参数是否在目标列表中（不区分大小写）
        if param_name.lower() in [p.lower() for p in target_params]:
            # 转换为首字母大写（每个单词的首字母大写）
            title_case_name = param_name.title().replace('_', ' ')
            return prefix + title_case_name
        else:
            return match.group(0)
    
    converted_content = re.sub(pattern, to_title_case, content, flags=re.IGNORECASE)
    
    if converted_content != content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(converted_content)
        print(f"文件已更新（首字母大写）: {file_path}")
        return True
    else:
        print(f"文件无需修改: {file_path}")
        return False

# 保持下划线版本的首字母大写
def convert_to_title_case_keep_underscore(file_path, target_params=None):
    """
    转换为首字母大写，但保持下划线
    """
    if target_params is None:
        target_params = ['ELEMENT', 'SEGMENT']
    
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    params_pattern = '|'.join(re.escape(param) for param in target_params)
    pattern = rf'(/begin\s+|\bend\s+)({params_pattern})'
    
    def to_title_case_underscore(match):
        prefix = match.group(1)
        param_name = match.group(2)
        
        if param_name.lower() in [p.lower() for p in target_params]:
            # 保持下划线的首字母大写
            parts = param_name.split('_')
            title_parts = [part.title() for part in parts]
            title_case_name = '_'.join(title_parts)
            return prefix + title_case_name
        else:
            return match.group(0)
    
    converted_content = re.sub(pattern, to_title_case_underscore, content, flags=re.IGNORECASE)
    
    if converted_content != content:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(converted_content)
        print(f"文件已更新（首字母大写，保持下划线）: {file_path}")
        return True
    else:
        print(f"文件无需修改: {file_path}")
        return False