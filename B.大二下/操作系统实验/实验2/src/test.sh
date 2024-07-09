#!/bin/bash

# 清屏
clear

# 提示用户输入要检测的文件名
echo -n "input file name: "
read filename

# 检查文件是否存在
if [ ! -f "$filename" ]; then
    echo "can not find file [$filename!]"
    exit 1
fi

# 显示文件状态信息
echo "current status of [$filename] is:"
ls -l "$filename"

# 保存文件大小信息
old_size=$(ls -l "$filename" | awk '{print $5}')

# 变化次数计数器
change_count=0
# 无变化次数计数器
no_change_count=0
# 最大允许无变化次数
max_no_change_count=10
# 最大允许变化次数
max_change_count=2

# 循环检测文件大小变化
while true; do
    # 每隔5秒钟检测一次文件大小信息
    sleep 5
    
    # 获取当前文件大小
    current_size=$(ls -l "$filename" | awk '{print $5}')
    
    # 比较文件大小是否改变
    if [ "$current_size" -ne "$old_size" ]; then
        echo "file [$filename] size changed!"
        ((change_count++))
        old_size=$current_size
    else
        echo "test file's status..."
        ((no_change_count++))
    fi
    
    # 如果文件大小已累计改变了两次，或者连续被检测了十次还未改变大小，则退出
    if [ "$change_count" -ge "$max_change_count" ] || [ "$no_change_count" -ge "$max_no_change_count" ]; then
        if [ "$change_count" -ge "$max_change_count" ]; then
            echo "change number exceed $max_change_count, test end!"
        else
            echo "Test number exceed $max_no_change_count!"
        fi
        break
    fi
done

# 清屏并退出
exit 0
