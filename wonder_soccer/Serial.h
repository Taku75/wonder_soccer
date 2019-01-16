#pragma once

#include <string>
#include <vector>

#ifndef _UNICODE
using Tstring = std::string;
using Tchar = char;
#else
using Tstring = std::wstring;
using Tchar = wchar_t;
#endif

class SerialInfo
{
private:
	Tstring port_name;
	Tstring device;

public:
	//�|�[�g��
	const Tstring& port() const;
	const Tstring& device_name() const;
	SerialInfo();
	SerialInfo(const SerialInfo&);
	SerialInfo(const Tstring& port);
	SerialInfo(const Tstring& port, const Tstring& device_name);
};

std::vector<SerialInfo> getSerialList();

class Serial
{
public:
	//�ݒ�
	struct Config
	{
		unsigned int baudRate;
		unsigned int byteSize;
		enum class Parity
		{
			NO,//�p���e�B�Ȃ�
			EVEN,//�����p���e�B
			ODD//��p���e�B
		}parity;

		enum class StopBits
		{
			//1�r�b�g
			ONE,
			//1.5�r�b�g
			ONE5,
			//2�r�b�g
			TWO
		}stopBits;
	};

private:
	//�|�[�g���
	SerialInfo info;

	//�I�[�v�����Ă邩
	bool opened;

	//�ݒ�
	Config conf;

	void* handle;
	void setBuffSize(unsigned long read, unsigned long write);

public:
	Serial();
	Serial(const Serial&) = delete;
	~Serial();

	//<sammary>
	//�o�b�t�@�Ɋi�[���ꂽ�f�[�^�̃o�C�g����Ԃ�
	//</sammary>
	int available();

	//<sammary>
	//�f�o�C�X���I�[�v��
	//</sammary>
	bool open(const Tstring& port_name, unsigned int baudRate = 9600);
	bool open(const SerialInfo& serial_info, unsigned int baudRate = 9600);

	//<sammary>
	//�f�o�C�X���N���[�Y
	//</sammary>
	void close();

	//<sammary>
	//�|�[�g���̎擾
	//</sammary>
	const Config& getConfig() const;

	//<sammary>
	//�|�[�g����ݒ�
	//</sammary>
	void setConfig(const Config&);

	//<sammary>
	//�f�o�C�X���̎擾
	//</sammary>
	const SerialInfo& getInfo() const;

	//<sammary>
	//�f�o�C�X���I�[�v�����Ă��邩
	//</sammary>
	bool isOpened() const;

	//<sammary>
	//size�o�C�g�������̓o�b�t�@�ɂ��邾����M
	//</sammary>
	int read(unsigned char* data, int size);

	//<sammary>
	//1�o�C�g��M
	//</sammary>
	unsigned char read1byte();

	//<sammary>
	//�o�b�t�@���ׂĎ�M
	//�Œ�1�o�C�g
	//</sammary>
	std::vector<unsigned char> read();

	//<sammary>
	//�o�b�t�@���N���A
	//</sammary>
	void clear();

	//<sammary>
	//�o�̓o�b�t�@���N���A
	//</sammary>
	void clearWrite();

	//<sammary>
	//���̓o�b�t�@���N���A
	//</sammary>
	void clearRead();

	//<sammary>
	//���M
	//</sammary>
	int write(unsigned char* data, int size);

	//<sammary>
	//���M
	//</sammary>
	int write(const std::vector<unsigned char>& data);
};