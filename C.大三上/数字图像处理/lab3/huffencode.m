%huffencode ������������� vector ���� Huffman ���룬���ر�����������ѹ�������ݣ��������Ϣ
function [zipped,info]=huffencode (vector)
    if ~isa(vector,'uint8')
        eror('input argument must be a uint8 vector');
    end
    [m,n]=size(vector);
    vector=vector(:)';
    f=frequency(vector); %����������ų��ֵĸ���
    symbols=find(f~=0); f=f(symbols);
    [f,sortindex]=sort(f); %�����Ű��ճ��ֵĸ��ʴ�С����
    symbols=symbols(sortindex); len=length(symbols);
    symbols_index=num2cell(1:len); codeword_tmp=cell(len,1);
    while length(f)>1 %���� huffman �����õ����ֱ����
        index1=symbols_index{1}; index2=symbols_index{2};
        codeword_tmp(index1)=addnode(codeword_tmp(index1),uint8(0));
        codeword_tmp(index2)=addnode(codeword_tmp(index2),uint8(1));
        f=[sum(f(1:2)) f(3:end)];
        symbols_index=[{[index1,index2]} symbols_index(3:end)];
        [f,sortindex]=sort(f);
        symbols_index=symbols_index(sortindex);
    end
    codeword=cell(256,1);
    codeword(symbols)=codeword_tmp;
    len=0;
    for index=1:length(vector) %�õ�����ͼ�����б�����
        len=len+length(codeword{double(vector(index))+1});
    end
    string=repmat(uint8(0),1,len);
    pointer=1;
    for index=1:length(vector) %������ͼ����б���
        code=codeword{double(vector(index))+1};
        len=length(code); string(pointer+(0:len-1))=code;
        pointer=pointer+len;
    end
    len=length(string);
    pad=8-mod(len,8); %�� 8 ������ʱ����� pad �� 0
    if pad>0
        string=[string uint8(zeros(1,pad))];
    end
    codeword=codeword(symbols);
    codelen=zeros(size(codeword));
    weights=2.^(0:23);
    maxcodelen=0;
    for index=1:length(codeword)
        len=length(codeword{index});
        if len>maxcodelen
            maxcodelen=len;
        end
        if len>0
            code=sum(weights(codeword{index}==1));
            code=bitset(code,len+1);
            codeword{index}=code;
            codelen(index)=len;
        end
    end
    codeword=[codeword{:}];
    %����ѹ���������
    cols=length(string)/8;
    string=reshape(string,8,cols);
    weights=2.^(0:7);
    zipped=uint8(weights*double(string)); %���洢��һ��ϡ�����
    huffcodes=sparse(1,1);
    for index=1:nnz(codeword) %length(codeword) %numel(codeword)
        huffcodes(codeword(index),1)=symbols(index);
    end
    info.pad=pad;
    info.huffcodes=huffcodes;
    info.ratio=cols./length(vector);
    info.length=length(vector);
    info.maxcodelen=maxcodelen;
    info.rows=m;
    info.cols=n;
