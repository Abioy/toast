toast��˽���������ķַ����Լ��������ռ�����Ϊcontroller��agent
1 Ŀ¼���ܼ�飺
agent Ϊtoast�ͻ���
agentcmdrsp agent��controller֮����Ϣ����
ciagent ��Ϊ�������ɶ�ʵ�ֵ�����agent��������û�ָ����svn��ַ������������ص�svn��ַ�µĴ���
        �и��£���ִ����Ӧ�Ĳ�������
config �����ļ��������
controller  Ϊtoast�ķ������ˣ��ַ�ǰ�˷��͵������ָ����agent�����ռ�����ִ�н��
daemon  unixϵͳdaemonize����
include ��������ľ�̬���ͷ�ļ���curl��json�� log4cpp
libs ��ž�̬�⣬������������Ŀ��ڱ�������������⣬��ֱ������Ӧ�Ŀ�
log  log��
net  �������
poll epoll�򵥷�װ
pty  α�ն˷�װ
sync �߳�ͬ����
threadpool �̳߳�
trayicon  windows�µ�����ͼ���
winagent  windows��agent�Ĺ����ļ�
2. ����

a. toastӦ�õ��Ŀ�Դ�����libcurl,libjson, log4cpp ��������controller��agent�����õ���
   ��3����Ӧ�þ�̬�⣬������libsĿ¼�����������⣬�������������������������⣬�밴
   ����˵���ĵ��ֱ���룬����̬�����libsĿ¼
   ����controller ���õ�rrdtool�� Ҫ����controller��Ҫrrdtool-devel
   ����svn���agent����Ҫsvnclient�⣬�����Ҫ��װsubversion-devel

b. ������пⶼ׼���ã�����Ҫ�ڸ�Ŀ¼Make����,agent����ӦagentĿ¼�ڣ�toast��
   ��controller��Ҫ������controllerĿ¼make
����������ƽ̨�±���ͨ����
rhel 5�� 6 centos 6 ��Ҫcontroller��Ҫrrdtool rrdtool-devel�� ciagent��Ҫlibsubversion-devel

ubuntu 12.04.1 
a. �ڸ�ƽ̨�±���controller��Ҫ��װrrdtool��librrd-dev
b. ��ubuntu�±���ciagent��Ҫ��װlibapr1-dev, libaprutil1-dev libsvn-dev�����п�����Ҫ�޸�make�ļ�
   -I/usr/include/apr-1 to -I/usr/include/apr-1.0 ͨ��apr-config --includes ȷ��ͷ�ļ���λ�ã����޸�
   LINK= -lpthread -ldl -lrt -lsvn_client-1 to LINK= -lpthread -ldl -lrt -lsvn_client-1 -lapr-1




��װ��
controller: 
Ҫ����controllerֻ��Ҫ���������controller��ִ���ļ���controller.conf �ļ�����
agent��
Ҫ����agent����Ҫ��������Ŀ�ִ���ļ�toast��AgentDaemon.conf����

��������н���Ҫ���ļ����룬����������㰲װ

3 �����ļ�˵��
a. agent
[]
server=yourcontrolleripordomainname     //controller��ip��������
port=16868                              // controller�˿�

[LOG]       // log4cpp����
# --- categories ---
log4cpp.rootCategory=DEBUG,MAIN

# --- root Appender ---
log4cpp.appender.MAIN=org.apache.log4cpp.RollingFileAppender
log4cpp.appender.MAIN.fileName=AgentDaemon.log
log4cpp.appender.MAIN.maxFileSize=10240000 
log4cpp.appender.MAIN.maxBackupIndex=100
log4cpp.appender.MAIN.layout=org.apache.log4cpp.PatternLayout
log4cpp.appender.MAIN.layout.ConversionPattern=%d{%Y-%m-%d %H:%M:%S} [%p]: %m%n

b. ciagent
[]
server=yourcontrollerordamain  // controller ip��������
port=16868                     // �˿�
CIGetListURL = http://yourcontrollerordamain/task/getallurl //��controller��ȡ����ci�����б�
CITaskURL = http://yourcontrollerordamain/api/runtaskbyid   //����ǰ�˴���һ���µ���������
CIInterval = 300                                 // svn ɨ���Ƶ��
svn_username="username"                           // svn username�����usernameҪ������ci����ķ���Ȩ�ޣ�ciֻ�൱��svn log����������ش��뵽����
svn_password="password"                           // svn password
[LOG]  // log4cpp����
# --- categories ---
log4cpp.rootCategory=DEBUG,MAIN

# --- root Appender ---
log4cpp.appender.MAIN=org.apache.log4cpp.RollingFileAppender
log4cpp.appender.MAIN.fileName=AgentDaemon.log
log4cpp.appender.MAIN.maxFileSize=10240000 
log4cpp.appender.MAIN.maxBackupIndex=100
log4cpp.appender.MAIN.layout=org.apache.log4cpp.PatternLayout
log4cpp.appender.MAIN.layout.ConversionPattern=%d{%Y-%m-%d %H:%M:%S} [%p]: %m%n

c. controller �����ļ�
[]
monitor_path = /tmp/toast     // controller����ǰ�������ļ�Ŀ¼����Ҫ��ǰ��������ã�controller����ɨ�����Ŀ¼������������ļ��������ִ�����Ȼ��ɾ������
rrd_path = /tmp/rra           // controller�����Լ�������Ϣ��rrd�ļ���ʽд�����Ŀ¼
log_path = /home/toast/output  // ����log�ļ�Ŀ¼�� controller�ռ����������stdout��stderr��Ϣ�����������ļ��У��ļ���Ϊ��Ӧִ��id����Щ������ڲ��Ի���ִ��
response_thread_num = 6        // controller ����agent��Ӧ��Ϣ���߳���
root_url = http://127.0.0.1/toast/   // ǰ��url�ĸ�
task_list_url = task/getallruntime?   // ��ȡǰ�˶�ʱ�����б�url��controller����ʱ���ǰ��ȡ��ʱ�����б�
add_agent_url = machine/addmachine?   // ��ӻ���api
agent_info_url = machine/updatemachine?  // ���»�����Ϣurl
update_all_agent_url = machine/updateallmachine? // �������в��Ի���Ϣ��Ϊ�˻���״̬��ͬ����controller��ÿ������ʱ������в��Ի�״̬����Ϊdown
update_all_run_url = run/updateallrun?           // ������������״̬��controller������ʱ���������������Ϊ���״̬
udate_run_url = run/updaterun?                   // ���µ��������״̬
run_timer_task_url = api/runtaskbyid?            // ����ǰ�˴���ĳ�������һ������api�������ڶ�ʱ����ʱʱ�䵽ʱӦ��
max_agent_number = 4096                          // ���agent����
CIAgent=cisvnmonitoragent                        // ci agent �Ļ�����������Ϊ������������ci������񶼻ᷢ�͵�������Ի�
[LOG]                             // log4cpp����
# --- categories ---
log4cpp.rootCategory = DEBUG,MAIN

# --- root Appender ---
log4cpp.appender.MAIN = org.apache.log4cpp.RollingFileAppender
log4cpp.appender.MAIN.fileName = controller.log
log4cpp.appender.MAIN.maxFileSize = 102400000
log4cpp.appender.MAIN.maxBackupIndex = 100
log4cpp.appender.MAIN.layout = org.apache.log4cpp.PatternLayout
log4cpp.appender.MAIN.layout.ConversionPattern = %d{%Y-%m-%d %H:%M:%S} [%p]: %m%n



��Щ���ô󲿷ֶ���ǰ��������أ���ο�ǰ�������Լ�ǰ���Э�鶨��,������ǰ����������Ӧ�޸�


