%函数 addnod 添加节点
function codeword_new=addnode(codeword_old,item)
    codeword_new=cell(size(codeword_old));
    for index=1:length(codeword_old)
        codeword_new{index}=[item codeword_old{index}];
    end


