
conn = database('stock', 'root', '','com.mysql.jdbc.Driver','jdbc:mysql://127.0.0.1:3366/stock')
curs = exec(conn,'select * from shanghai_index');
curs = fetch(curs); % �����ݶ��� matlab �Ŀռ���
close(conn);
timeAxis = curs.Data(:,1);
timeA = cell2mat(timeAxis);
szindex = cell2mat(curs.Data(:,2));
self_index = cell2mat(curs.Data(:,6));
timeB = datenum(timeA); % ���ַ����͵����� ת���� ��ֵ��
plot(timeB, szindex, 'LineWidth',1, 'Color', 'r');
hold on;
plot(timeB, self_index, 'LineWidth',1, 'Color', 'g');
% �� x ��������ڸ�ʽ����ʾ, keepticks ѡ��������� label ���ܶ�
datetick('x', 'yyyy/mm/dd','keepticks');   
