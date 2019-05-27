#include "StdAfx.h"
#include "GbUsageEnvironment.h"

#include "InviteWithoutSDP.h"

CInviteWithoutSDP::CInviteWithoutSDP(CGbUsageEnvironment& env, sipd_media_session * pMediaSession)
:Medium(env)
{
	stringstream ss;
	// Step 2
	m_sipd_sdp_info.cid = pMediaSession->cid;
	m_sipd_sdp_info.did = pMediaSession->did;
	m_sipd_sdp_info.tid = pMediaSession->tid;

	/* ����SDP */
	m_channel_id = string(pMediaSession->channel_id);

	env.m_lst_invite_without_sdp.push_back(this);

	ss << "CInviteWithoutSDP ���죬cid = " << m_sipd_sdp_info.cid ;

	LOG4CPLUS_DEBUG(g_logger, ss.str().c_str() );
}

CInviteWithoutSDP::~CInviteWithoutSDP(void)
{
	stringstream ss;

	list<Medium *>::iterator it = ((CGbUsageEnvironment&)envir()).m_lst_invite_without_sdp.begin();
	for(; it!=((CGbUsageEnvironment&)envir()).m_lst_invite_without_sdp.end(); it++)
	{
		if(*it== this)
		{
			((CGbUsageEnvironment&)envir()).m_lst_invite_without_sdp.erase(it);
			break;
		}
	}

	ss << " ~CInviteWithoutSDP ���� ��cid = " << m_sipd_sdp_info.cid ;

	LOG4CPLUS_DEBUG(g_logger, ss.str().c_str() );
}


void CInviteWithoutSDP::Send_200_OK()
{
	stringstream ss;

	// SDP������ý��������Ľ��յ�ַ���˿ڡ�����ý�����͵Ƚ�����Ϣ, ������ SSRC
	sipd_message_query_or_response  msg;
	memset(&msg, 0 , sizeof(sipd_message_query_or_response));
	msg.cid = m_sipd_sdp_info.cid;
	msg.tid = m_sipd_sdp_info.tid;
	msg.did = m_sipd_sdp_info.did;

	snprintf(msg.body,MAX_SIPD_BODY_LENGTH,
		"v=0\r\n"\
		"o=%s 0 0 IN IP4 %s\r\n"\
		"i=%s\r\n"\
		"c=IN IP4 %s\r\n"\
		"t=0 0\r\n"\
		/*"m=video %d RTP/AVP %d %d\r\n"\*/
		"m=video %d RTP/AVP %d\r\n"\
		"a=recvonly\r\n"\
		/*"a=rtpmap:%d PS/90000\r\n"\*/
		"a=rtpmap:%d PS/90000\r\n"\
		/*"a=username:%s\r\n"\*/
		/*"a=password:%s\r\n"\*/
		/*"y=%s\r\n"*/ ,
		g_strLocalDomainID.c_str(), g_strLocalIP.c_str(), "GB28181 DEVICE", g_strLocalIP.c_str(),
		g_iRtpPort, SIP_PS_H264, SIP_PS_H264);

	build_and_send_invite_200_ok(&msg, 1);
}


void CInviteWithoutSDP::Receive_ACK(sipd_media_session * pMediaSession)
{
	/* SDP��������ý�巢���ߵķ��͵�ַ���˿ڡ�����ý�����͵ȷ�����Ϣ��
	 �յ��󽫶�Ӧ��ϵ <Subject �з����߱��롢SDP �е� ssrc > ���� */

	stringstream ss;

	((CGbUsageEnvironment&)envir()).m_sender_ssrc[string(pMediaSession->o_id)] = string(pMediaSession->ssrc);

	ss << " CInviteWithoutSDP-->Receive_ACK ��cid = " << m_sipd_sdp_info.cid ;
	ss << ", o_id = " << string(pMediaSession->o_id) << ", ssrc = " << string(pMediaSession->ssrc);
	LOG4CPLUS_DEBUG(g_logger, ss.str().c_str() );
}

void CInviteWithoutSDP::Receive_BYE(sipd_media_session * pMediaSession)
{
	stringstream ss;
	ss << " CInviteWithoutSDP-->Receive_BYE ��cid = " << m_sipd_sdp_info.cid ;
	LOG4CPLUS_DEBUG(g_logger, ss.str().c_str() );

	((CGbUsageEnvironment&)envir()).m_sender_ssrc.erase(string(pMediaSession->channel_id));

	sipd_message_query_or_response  msg;
	memset(&msg, 0 , sizeof(sipd_message_query_or_response));
	msg.cid = m_sipd_sdp_info.cid;
	msg.tid = m_sipd_sdp_info.tid;
	msg.did = m_sipd_sdp_info.did;

	build_and_send_invite_200_ok(&msg, 0);

	Medium::close(this);
}