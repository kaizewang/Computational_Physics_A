f=fullfile('C:\Users\91922\Desktop\��������\RW\Task3_endpoint_distribution','rw_endpoints_5steps.txt');
fidin=fopen(f);                               % ��test2.txt�ļ�
fidout=fopen('mkmatlab.txt','w');                       % ����MKMATLAB.txt�ļ�
while ~feof(fidin)                                      % �ж��Ƿ�Ϊ�ļ�ĩβ
tline=fgetl(fidin);                                 % ���ļ�����
if (double(tline(1))>=48&&double(tline(1))<=57)...
        ||double(tline(1))==45||double(tline(1)==32)      % �ж����ַ��Ƿ�����ֵ
fprintf(fidout,'%s\n\n',tline);                  % ����������У��Ѵ�������д���ļ�MKMATLAB.txt
continue                                         % ����Ƿ����ּ�����һ��ѭ��
end
end
fclose(fidout);
MK=importdata('MKMATLAB.txt');      % �����ɵ�MKMATLAB.txt�ļ����빤���ռ䣬������ΪMK��ʵ����������ʾ����