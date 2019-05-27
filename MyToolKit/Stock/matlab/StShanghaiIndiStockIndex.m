function handleNumber = StShanghaiIndiStockIndex( windowNumber, startDate, endDate, stockCode )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
handle = figure(str2num(windowNumber));
handleNumber = handle.Number;

% ��մ���
clf;

conn = database('stock', 'root', '','com.mysql.jdbc.Driver','jdbc:mysql://127.0.0.1:3366/stock');
strSql = 'select tradedate, close_index  from daily_hushen_stock where tradedate >=''';
strSql = strcat(strSql, startDate);
strSql = strcat(strSql, ''' and tradedate <= ''');
strSql = strcat(strSql, endDate);
strSql = strcat(strSql, ''' and code = ');

% �����ݶ��� matlab �Ŀռ���
% ��ȡ��ָ֤��
strSql_ = strcat(strSql, int2str(1));
curs = exec(conn, strSql_);
curs = fetch(curs);
szTradedate = cell2mat(curs.Data(:,1));
szTradedate = datenum(szTradedate); 
szIndex = cell2mat(curs.Data(:,2));
% ��ȡ����ָ��
strSql_ = strcat(strSql, int2str(stockCode));
curs = exec(conn, strSql_);
curs = fetch(curs);
indiTradedate = cell2mat(curs.Data(:,1));
indiTradedate = datenum(indiTradedate); 
indiIndex = cell2mat(curs.Data(:,3));

close(conn);

% ȥ��ͼ����Χ�ı߿���ͼ����ʾ�ĸ���
grid on;
set(gca,'looseInset',[10 10 10 10]);   
% ����˫��ͼ
plotyy(szTradedate, szIndex, indiTradedate, indiIndex, 'plot', 'plot');

% �� x ��������ڸ�ʽ����ʾ, keepticks ѡ��������� label ���ܶ�
datetick('x', 'yyyy/mm/dd','keepticks');  
legend('��ָ֤��', '����ָ��');

strTitle = strcat('��ѯ���ڷ�Χ��' ,startDate, ' �� ', endDate);
title(strTitle);
end

