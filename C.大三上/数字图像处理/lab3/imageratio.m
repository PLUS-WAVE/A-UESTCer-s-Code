%函数 imageratio 计算两个图像压缩比
function cr=imageratio(f1,f2)
    error(nargchk(2,2,nargin));
    cr=bytes(f1)/bytes(f2);
