


//���洢��֡��Ϣ
#define MAX_FRAME_NUM 10000
//���洢��Packet��Ϣ
#define MAX_PACKET_NUM 10000
//URL����
#define MAX_URL_LENGTH 500


//��̬����ֻ�������������ļ����пɼ������ܱ������ļ������ã�Ҳ����˵�þ�̬����ֻ
//�����䶨���.cpp��.c�е��ã�������.cpp��.c�ļ��ĺ������ǲ��ܱ����õġ���
//��Ҫ��static void toggle_pause(VideoState *is)���з�װ

//���͡���ͣ������
//Send Command "Pause"
void ffmfc_play_pause();

//���͡���֡������
//Send Command "Step"
void ffmfc_seek_step();

//���͡�ȫ��������
//Send Command "FullScreen"
void ffmfc_play_fullcreen();

//���͡�ǰ��/���ˡ�����
//Send Command "Seek"
void ffmfc_seek(int time);

//���͡���߱ȡ�����
//Send Command "AspectRatio"
void ffmfc_aspectratio(int num,int den);

//���͡���С������
//Send Command "WindowSize"
void ffmfc_size(int percentage);

//���͡����ڻ������ݡ�����
//Send Command "Audio Display Mode"
void ffmfc_audio_display(int mode);

//���͡��˳�������
//Send Command "Quit"
void ffmfc_quit();

//����������
//Main function
int ffmfc_play(LPVOID lpParam);

//��λ
//Reset
int ffmfc_reset_index();

//���Ž���
//Seek Bar
void ffmfc_seek_bar(int pos);
//Stretch
void ffmfc_stretch(int stretch);



int do_init();
int do_stream_open(CustomEventData * data1);