%函数 decode 返回码字对应的符号
function byte=decode(code,info)
    byte=info.huffcodes(code);

