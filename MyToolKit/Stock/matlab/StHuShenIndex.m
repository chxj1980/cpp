function handleNumber = StHuShenIndex( windowNumber, startDate, endDate, indexCode )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
handle = figure(str2num(windowNumber));
handleNumber = handle.Number;

% ��մ���
clf;

 % �����ݶ��� matlab �Ŀռ���
conn = database('stock', 'root', '','com.mysql.jdbc.Driver','jdbc:mysql://127.0.0.1:3366/stock');
strSql = 'select * from daily_hushen_plate where tradedate >''';
strSql = strcat(strSql, startDate, ''' and tradedate <= ''',endDate, ''' and code = ', indexCode);

curs = exec(conn, strSql);
curs = fetch(curs);
timeA = cell2mat(curs.Data(:,4));
timeA = datenum(timeA);
point = cell2mat(curs.Data(:,8));

strSql = 'select tradedate, close from sohuindexdaily where tradedate >''';
strSql = strcat(strSql, startDate, ''' and tradedate <= ''',endDate, ''' and code = ', indexCode);
curs = exec(conn, strSql);
curs = fetch(curs);
timeB = cell2mat(curs.Data(:,1));
timeB = datenum(timeB);         % ���ַ����͵����� ת���� ��ֵ��
szindex = cell2mat(curs.Data(:,2));
close(conn);

plot(timeA, point, 'LineWidth',1, 'Color', 'r');
hold on;
plot(timeB, szindex, 'LineWidth',1, 'Color', 'g');
% �� x ��������ڸ�ʽ����ʾ, keepticks ѡ��������� label ���ܶ�
datetick('x', 'yyyy/mm/dd','keepticks'); 
if str2num(indexCode) == 1 
    legend('ģ����֤��ָ', '��֤��ָ');
elseif str2num(indexCode) == 399101
    legend('ģ����С����ָ', '��С����ָ');    
elseif str2num(indexCode) == 399102
    legend('ģ�ⴴҵ����ָ', '��ҵ����ָ');
else
    
end;    
grid on;

strTitle = strcat('��ѯ���ڷ�Χ��' ,startDate, ' �� ', endDate);
title(strTitle);
end

