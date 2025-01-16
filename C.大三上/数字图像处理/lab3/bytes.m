%函数 bytes 返回输入 f 占用的比特数
function b=bytes(f)
    if ischar(f)
        info=dir(f);
        b=info.bytes;
    elseif isstruct(f)
        b=0;
        fields=fieldnames(f);
        for k=1:length(fields)
            b=b+bytes(f.(fields{k}));
        end
    else
        info=whos('f');
        b=info.bytes;
    end
