function handleNumber = StShenzhenIndexPlateIndex( windowNumber, startDate, endDate, graphOrTable, plateCodes )
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
handle = figure(str2num(windowNumber));
handleNumber = handle.Number;

% ��մ���
clf;

conn = database('stock', 'root', '','com.mysql.jdbc.Driver','jdbc:mysql://127.0.0.1:3366/stock');

% �����ݶ��� matlab �Ŀռ���
strSql = 'select name, tradedate, close as point from szse_index_daily where tradedate >=''';
strSql = strcat(strSql, startDate);
strSql = strcat(strSql, ''' and tradedate <= ''');
strSql = strcat(strSql, endDate);
strSql = strcat(strSql, ''' and code = ');

hwait = waitbar(0,'��ȴ�......','WindowStyle','modal');
totalNum = length(plateCodes);
j = 1;
for i = 1: totalNum
    strSql_ = strcat(strSql, int2str(plateCodes(i)));
    curs = exec(conn, strSql_);
    curs = fetch(curs);
    %     strSql_ = strcat(strSql_, '''');
    if ~strcmp(curs.Data,'No Data')
        areaIndex(j).name = cell2mat(curs.Data(:, 1));
        areaIndex(j).code = int2str(plateCodes(i));
        
        areaIndex(j).tradedate = cell2mat(curs.Data(:, 2));
        areaIndex(j).point = cell2mat(curs.Data(:, 3))
        j = j + 1;
    end;
    
    str=['����������',num2str(i/totalNum * 100),'%'];
    waitbar(i/totalNum, hwait, str);
    close(curs);
end;
close(hwait);
close(conn);

strTitle = strcat('��ѯ���ڷ�Χ��' ,startDate, ' �� ', endDate);
title(strTitle);

if strcmp(graphOrTable, 'Graph')
    % �������ߵĻ���
    hwait = waitbar(0,'��ͼ�У���ȴ�......','WindowStyle','modal');
    totalNum = length(areaIndex);
    
    hold on;
    grid on;
    set(gca,'looseInset',[10 10 10 10]);   % ȥ��ͼ����Χ�ı߿���ͼ����ʾ�ĸ���
    
    for i = 1: totalNum
        timeB = datenum(areaIndex(i).tradedate); % ���ַ����͵����� ת���� ��ֵ��
        ph(i) = plot(timeB, areaIndex(i).point, 'LineWidth',1, 'ButtonDownFcn', @lincbf);
        label(i) = {areaIndex(i).name(1, :)};
        %  ������ĩ������ڳ��ı仯��
        len = length(areaIndex(i).point);
        if len > 0
            change_rate = areaIndex(i).point(len) -  areaIndex(i).point(1);
            change_rate = change_rate/ areaIndex(i).point(1) * 100;
            label(i) = strcat(label(i), '��', int2str(change_rate), '%');
            
            set(ph(i), 'Tag', label{i});
        end;
        
        str=['��ͼ�У���ȴ�......',num2str(i/totalNum * 100),'%'];
        waitbar(i/totalNum,hwait,str);
    end;
    close(hwait);
    legend(ph, label, 'Location','EastOutside');
    datetick('x', 'yyyy/mm/dd','keepticks');
    
else
    %   �Ա����ʽչʾ
    columnname =   {'����', '����', '�ڳ�����', '��ĩ����', '�ڳ���λ', '��ĩ��λ', '�ǵ���(%)' };
    columnformat = {'numeric', 'char', 'char', 'char', 'bank', 'bank', 'bank'};
    ColumnWidth = {'auto', 200, 'auto', 'auto', 'auto', 'auto', 'auto'};
    for i = 1: length(areaIndex)
        [len, cols] = size(areaIndex(i).tradedate);
        dat(i, 1) = { areaIndex(i).code };
        dat(i, 2) = { areaIndex(i).name(1,:) };
        dat(i, 3) = { areaIndex(i).tradedate(1, :) };
        dat(i, 4) = { areaIndex(i).tradedate(len, :) };
        dat(i, 5) = { areaIndex(i).point(1) };
        dat(i, 6) = { areaIndex(i).point(len) };
        dat(i, 7) = { (areaIndex(i).point(len) - areaIndex(i).point(1))/ areaIndex(i).point(1) * 100  };
    end;
    
    %   �� Units = normalized ʱ�� The lower-left corner of the container maps to (0,0) and the upper-right corner maps to (1,1).
    t = uitable(handle, 'Units','normalized',...
        'Data', dat,...
        'Position', [0.05 0.05 0.9 0.88],...
        'FontSize',10,...
        'ColumnName', columnname,...
        'ColumnFormat', columnformat,...
        'ColumnWidth', ColumnWidth,...
        'RearrangeableColumns', 'on');
    
    c = uicontextmenu;
    t.UIContextMenu = c;
    
    % Create child menu items for the uicontextmenu
    m1 = uimenu(c,'Label','��ĩ��λ-����','Callback',@setlinestyle);
    m3 = uimenu(c,'Label','��ĩ��λ-�ݼ�','Callback',@setlinestyle);
    m2 = uimenu(c,'Label','�ǵ���-����','Callback',@setlinestyle);
    m4 = uimenu(c,'Label','�ǵ���-�ݼ�','Callback',@setlinestyle);
end;

    function lincbf(src,eventdata)
        % ���Ҽ����Ҫɾ��������
        strLegend = get(src, 'Tag');
        strTitle_ = strcat(strTitle, '��' ,strLegend);
        title(strTitle_);
        if strcmp(get(gcf,'SelectionType'),'alt')
            delete(src) % ɾ������
        end
    end

    function setlinestyle(source,callbackdata)
        switch source.Label
            case '��ĩ��λ-����'
                dat = sortrows(dat, 6);
                set(t,'data',dat);
            case '�ǵ���-����'
                dat = sortrows(dat, 7);
                set(t,'data',dat);
            case '��ĩ��λ-�ݼ�'
                dat = sortrows(dat, -6);
                set(t,'data',dat);
            case '�ǵ���-�ݼ�'
                dat = sortrows(dat, -7);
                set(t,'data',dat);
                
        end
    end
end

