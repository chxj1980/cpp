function  stocktest(wndname, surface)
%UNTITLED3 �˴���ʾ�йش˺�����ժҪ
%   �˴���ʾ��ϸ˵��
figure('NumberTitle','off','MenuBar','None','ToolBar','None','Name',wndname);
switch surface
    case 'sphere'
        sphere
    case 'cylinder'
        cylinder
end
shading interp
axis equal
end

