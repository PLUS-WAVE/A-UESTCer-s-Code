%函数 frequency 计算各个符号出现的概率
function f=frequency(vector)
    if ~isa(vector,'uint8')
        error('input argument must be a uint8 vector');
    end
    f=repmat(0,1,256);
    len=length(vector);
    for index=0:255
        f(index+1)=sum(vector==uint8(index));
    end
    f=f./len;

