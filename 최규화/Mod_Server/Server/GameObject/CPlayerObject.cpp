#include "CPlayerObject.h"

CPlayerObject::~CPlayerObject()
{
	if (scene != nullptr)
		delete scene;

	if (m_bullObj != nullptr)
		delete m_bullObj;
}

bool CPlayerObject::CheckPlayerInfo()
{
	scene = new CScene();
	//접속연결시 플레이어의 아이디 m_playerIndex (ai + player)
	/*
	CTextTest DB;
	Packet cur_logindata_packet[MAX_BUFFER_SIZE]{ 0 };
	Player_LoginDB logindata;
	
	m_socket.receive(boost::asio::buffer(cur_logindata_packet, MAX_BUFFER_SIZE));
	
	wcscpy(m_loginID, reinterpret_cast<wchar_t*>(&cur_logindata_packet[1]));
	wcscpy(m_loginPW, reinterpret_cast<wchar_t*>(&cur_logindata_packet[cur_logindata_packet[0] + 4]));
	
	wcscpy(logindata.name, m_loginID); wcscpy(logindata.password, m_loginPW);
	DB.loginDataList.emplace_back(logindata);
	
	if ((wcscmp(L"guest", m_loginID) == 0) && (wcscmp(L"guest", m_loginPW) == 0))
	{
		cur_logindata_packet[0] = 1;
		m_socket.send(boost::asio::buffer(cur_logindata_packet, MAX_BUFFER_SIZE));
	
		m_connect = true;
	
		//m_staticobject = new StaticObject();
	
		return true;
	}
	*/
	return true;
}

void CPlayerObject::Init_MonsterInfo()
{
}

void CPlayerObject::Init_PlayerInfo()
{
	m_state = IDLE;

	m_ani = Ani_State::Idle;
	m_connect = true;
	m_dir = 0;
	m_airbone = false;
	m_ai = false;
	m_rot4f = { 0.f, 0.f, 0.f, 1.f };
	m_godmode = false;
	m_fixed = false;
	m_alive = true;
	m_type = OBJECT_TYPE::PLAYER;

	m_ability.attack = 10;
	m_ability.curHP = 100;
	m_ability.orignHP = 100;
	m_ability.exp = 0;
	m_ability.level = 1;
	m_ability.speed = 50;

	if (m_id == 0)
		m_pos4f = { -100.f, -1000.f, 0.f, 0.f};
	else if (m_id == 1)
		m_pos4f = { 300.f, -1000.f, 0.f, 0.f };

	m_OffLookvector = XMFLOAT3(0, 0, -1);
	m_OffRightvector = XMFLOAT3(-1, 0, 0);

	XMFLOAT4 xmf4_rot{ m_rot4f.x, m_rot4f.y, m_rot4f.z, m_rot4f.w };
	auto q = XMLoadFloat4(&xmf4_rot);
	XMFLOAT3 axis{ 0,1,0 };
	auto q2 = QuaternionRotation(axis, MMPE_PI);
	xmf4_rot = QuaternionMultiply(xmf4_rot, q2);
	m_rot4f.x = xmf4_rot.x; m_rot4f.y = xmf4_rot.y; m_rot4f.z = xmf4_rot.z; m_rot4f.w = xmf4_rot.w;

	UpdateLookvector();
	UpdateUpvector();

	//물리효과 및 충돌처리를 위한 PhysicsPoint 클래스
	pp = new PhysicsPoint();
	pp->SetPosition(m_pos4f.x, m_pos4f.y, m_pos4f.z);
	pp->SetHalfBox(3, 10, 3);
	pp->SetDamping(0.7);
	pp->SetBounce(false);
	//

	//2. 물리효과 적용
	GravitySystem(0);

	XMFLOAT4 xmf4_pos{ m_pos4f.x, m_pos4f.y, m_pos4f.z, m_pos4f.w };
	pp->integrate(0, &xmf4_pos);
	m_pos4f.x = xmf4_pos.x;  m_pos4f.y = xmf4_pos.y; m_pos4f.z = xmf4_pos.z; m_pos4f.w = xmf4_pos.w;

	AfterGravitySystem(0);
	
	//wcscpy(m_pdata.LoginData.name, m_loginID);
	//wcscpy(m_pdata.LoginData.password, m_loginPW);
}

void CPlayerObject::InitData_To_Client()
{
	STC_SetMyClient stc_init;

	Player_Data pdata;
	pdata.pos = m_pos4f;
	pdata.rot = m_rot4f;
	pdata.ai = m_ai;
	pdata.airbone = m_airbone;
	pdata.ani = m_ani;
	pdata.connect = m_connect;
	pdata.dir = m_dir;
	pdata.godmode = m_godmode;
	pdata.id = m_id;
		 
	pdata.status.attack = m_ability.attack;
	pdata.status.speed = m_ability.speed;
	pdata.status.origin_hp = m_ability.orignHP;
	pdata.status.cur_hp = m_ability.curHP;
	pdata.status.exp = m_ability.exp;
	pdata.status.level = m_ability.level;
	
	stc_init.player_data = move(pdata);

	scene->m_clients[m_id]->SendPacket(reinterpret_cast<Packet*>(&stc_init));


}

void CPlayerObject::RegularUpdate()
{
}


void CPlayerObject::SendPacket(Packet * packet)
{
	int packet_size = packet[0];
	Packet *new_sendBuf = new Packet[packet_size];
	memcpy(new_sendBuf, packet, packet_size);

	//1. async_write_some - 비동기 IO / 받은데이터를 즉시 보냄(따로 버퍼에 저장X)
	//2. async_write - 비동기 IO / 보내고자 하는 데이터가 모두 버퍼에 담기면 데이터를 보냄
	boost::asio::async_write(m_socket, boost::asio::buffer(new_sendBuf, packet_size),
		[=](const boost::system::error_code& error, const size_t& bytes_transferred)
	{
		if (!error)
		{
			if (bytes_transferred != packet_size)
			{
				cout << "Client No. [ " << m_id << " ] async_write error code : " << error.value() << endl;
			}

			delete[] new_sendBuf;
			return;
		}
	});
}

void CPlayerObject::RecvPacket()
{
	//m_socket.async_read_some(boost::asio::buffer(m_recvBuf, MAX_BUFFER_SIZE),
	//[=](const boost::system::error_code& error, size_t bytes_transferred)

	//패킷받을 때 버퍼사이즈는 전달된 버퍼의 크기만큼만 할당해야한다
	//1바이트를 받아 패킷사이즈를 알고 해당 패킷 사이즈를 이용해 다시 패킷을 받는다
	//boost::asio::async_read(m_socket, boost::asio::buffer(m_recvBuf , 1),
	//	[&](const boost::system::error_code& error, size_t bytes_transferred)
	m_socket.async_read_some(boost::asio::buffer(m_recvbuf, MAX_BUFFER_SIZE),
		[&](const boost::system::error_code& error, const size_t& bytes_transferred)
	{
		//cout << "Bytes_Transferred: " << bytes_transferred << endl;
		// error = 0 성공 , error != 0 실패
		if (error)  // !error = 에러안났을때
		{
			STC_Disconnected disconnect_data;
			disconnect_data.connect = false;
			disconnect_data.id = m_id;

			// AI와 연결이 이미 끊긴 클라이언트에게는 연결을 끊으라는 패킷을 보내지 않는다
			for (auto client : m_clients)
			{
				if (client->Get_ID() == disconnect_data.id) continue;
				if (client->Get_IsAI() != true && client->Get_Connect_State() != false)
				{
					client->SendPacket(reinterpret_cast<Packet*>(&disconnect_data));
				}
			}


			//에러: 작업이 취소된 경우 
			cout << "Client No. [ " << m_id << " ] error code : " << error.value() << endl;

			cout << "IP: " << m_socket.remote_endpoint().address().to_string() << " // ";
			cout << "PORT: " << m_socket.remote_endpoint().port() << endl;

			// 자신의 연결상태 - 끊음
			SetState(DISCONNECT);

			m_connect = false;
			// shutdown_both - 주고 받는 쪽 모두를 중단
			m_socket.shutdown(m_socket.shutdown_both);
			m_socket.close();

			return;
		}

		int cur_data_proc = static_cast<int>(bytes_transferred);
		Packet* temp_buf = m_recvbuf;

		while (cur_data_proc > 0)
		{
			if (m_curr_packet_size == 0)			//이렇게 해야 패킷의 첫 정보는 무조건 패킷사이즈가 됨
			{
				m_curr_packet_size = temp_buf[0];
				if (temp_buf[0] > MAX_BUFFER_SIZE)
				{
					cout << "RecvPacket() Error, Client No. [ " << m_id << " ] recvBuf[0] is out of MAX_BUF_SIZE\n";
					exit(-1);
				}
			}

			int need_to_read = m_curr_packet_size - m_prev_packet_size;

			if (need_to_read <= cur_data_proc)
			{
				memcpy(m_databuf + m_prev_packet_size, temp_buf, need_to_read);

				ProcessPacket(m_databuf);

				cur_data_proc -= need_to_read;
				temp_buf += need_to_read;
				m_prev_packet_size = 0;
				m_curr_packet_size = 0;

				//cout << "cur_data_proc: " << cur_data_proc << " --- " << "need_to_read: " << need_to_read << endl;
			}
			else
			{
				memcpy(m_databuf + m_prev_packet_size, temp_buf, cur_data_proc);
				m_prev_packet_size += cur_data_proc;
				cur_data_proc -= cur_data_proc;
				temp_buf += cur_data_proc;
			}
		}

		RecvPacket();
	});
}

void CPlayerObject::ProcessPacket(Packet * packet)
{
	//packet[0] - 패킷의 사이즈
	//packet[1] - 해당 패킷이 하는일
	//packet[2] - 해당 패킷에 담겨진 데이터들

	switch (packet[1])
	{

	case PACKET_PROTOCOL_TYPE::CHANGED_PLAYER_POSITION:
	{
		if (m_state == DEAD)
			break;

		//1. 받아들인 데이터(키를 눌러 플레이어를 움직였음)에서 변화된 정보를 추출(물리효과 적용x)
		auto PosMove_Data = reinterpret_cast<STC_ChangedPos*>(packet);

		if (PosMove_Data->deltime < 0)
			PosMove_Data->deltime = 0.f;

		if (PosMove_Data->ani_state == Ani_State::Idle)
			m_state = IDLE;
		else if (PosMove_Data->ani_state == Ani_State::Run)
			m_state = MOVE;

		//2. 물리효과 적용
		pp->SetPosition(PosMove_Data->pos.x, PosMove_Data->pos.y, PosMove_Data->pos.z);
		pe->GravitySystem(PosMove_Data->deltime, pp);

		XMFLOAT4 xmf4{ PosMove_Data->pos.x, PosMove_Data->pos.y, PosMove_Data->pos.z, PosMove_Data->pos.w };
		pp->integrate(PosMove_Data->deltime, &xmf4);
		PosMove_Data->pos.x = xmf4.x; PosMove_Data->pos.y = xmf4.y;  PosMove_Data->pos.z = xmf4.z;  PosMove_Data->pos.w = xmf4.w;

		pe->AfterGravitySystem(PosMove_Data->deltime, pp, OBJECT_TYPE::PLAYER, PosMove_Data->pos, m_pdata.airbone);

		//3. 이동 - (애니메이션, 위치 변경) 변경된 데이터를 서버에서관리하는 내 클라이언트에 저장
		m_clients[PosMove_Data->id]->m_pdata.pos = move(PosMove_Data->pos);
		m_clients[PosMove_Data->id]->m_pdata.ani = PosMove_Data->ani_state;

		//cout << "ID: " << PosMove_Data->id << " 변화된 위치값: " << "[x:" << PosMove_Data->pos.x << "\t" << "y:" << PosMove_Data->pos.y
		//	<< "\t" << "z:" << PosMove_Data->pos.z << "]" << "\t" << "w:" << PosMove_Data->pos.w << endl;

		//4. 변화된 내 (포지션, 애니메이션) 정보를 다른 클라에 전달 - 반드시 이렇게 다시 만들어줘야함
		//PosMove_Data를 바로 sendpacket에 packet으로 형변화하여 보내면 size error가 난다
		STC_ChangedPos c_to_other;

		c_to_other.id = PosMove_Data->id;
		c_to_other.ani_state = m_pdata.ani;
		c_to_other.pos = move(m_pdata.pos);

		for (auto client : m_clients)
		{
			//상대가 ai / 연결끊김 / 나일 경우 보낼 필요 없음
			if (client->m_pdata.ai == true) continue;
			if (client->m_pdata.connect == false) continue;

			//if (client->m_pdata.ID == PosMove_Data->id) continue;
			//여기서 문제

			//갱신된 나의 데이터를 상대방에게 전달
			client->SendPacket(reinterpret_cast<Packet*>(&c_to_other));
		}

	}
	break;

	case PACKET_PROTOCOL_TYPE::PLAYER_ROTATE:
	{
		if (m_state == DEAD)
			break;

		m_state = ROTATE;

		auto Rotation_Data = reinterpret_cast<STC_Rotation*>(packet);

		// 1. 받은 정보를 내 클라이언트에 넣어주고
		m_clients[Rotation_Data->id]->m_pdata.rot = move(Rotation_Data->rotate_status);

		// 2. 받은 정보를 토대로 lookvector와 rightvector를 업데이트
		//m_clients[Rotation_Data->id]->UpdateLookVector(); //이거넣으면 20byte -> 21byte씩 다시보내게됨
		UpdateLookvector();
		UpdateUpvector();

		//cout << "ID: " << Rotation_Data->id << " 변화된 회전값: " << "[ x, y, z, w ]: "
		//	<< Rotation_Data->rotate_status.x << ", " << Rotation_Data->rotate_status.y << ", " << Rotation_Data->rotate_status.z << ", " << Rotation_Data->rotate_status.w << endl;

		// 3. 다른 클라에게 보낸다.
		STC_Rotation r_to_other;
		r_to_other.id = Rotation_Data->id;
		r_to_other.rotate_status = move(Rotation_Data->rotate_status);

		for (auto client : m_clients)
		{
			if (static_cast<bool>(client->m_pdata.ai) == true) continue;
			if (static_cast<bool>(client->m_pdata.connect) == false) continue;
			//if (client->m_pdata.ID == Rotation_Data->id) continue;

			client->SendPacket(reinterpret_cast<Packet*>(&r_to_other));
		}

	}
	break;

	case PACKET_PROTOCOL_TYPE::PLAYER_ATTACK:
	{
		if (m_state == PLAYER_STATE::DEAD)		break;

		auto n_bldata = reinterpret_cast<STC_Attack*>(packet);

		//공격키를 눌렀을 시, 불렛 생성.
		//불렛을 생성한 캐릭터 ID, 유도를 대비한 타겟 ID, 불렛 초기생성위치, 불렛 초기회전값, 불렛 생성시간, 불렛아이디
		m_bullObj = new CBulletObject(n_bldata->bull_data.Master_ID, n_bldata->bull_data.myID,
			n_bldata->bull_data.pos, n_bldata->bull_data.Rotate_status, n_bldata->lifetime,
			n_bldata->bull_data.vel3f, n_bldata->bull_data.type, n_bldata->bull_data.endpoint);

		//불렛 데이터 하나의 물리효과 적용해주기 (integrate -> aftergravity) -> set bullet start time
		m_bullObj->GetPhysicsPoint()->SetVelocity(n_bldata->bull_data.vel3f.x, n_bldata->bull_data.vel3f.y, n_bldata->bull_data.vel3f.z);
		m_bullObj->GetPhysicsPoint()->integrate(n_bldata->lifetime, reinterpret_cast<XMFLOAT4*>(&n_bldata->bull_data.pos));
		m_bullObj->AfterGravitySystem(n_bldata->lifetime);
		m_bullObj->SetBulletLifeTime(n_bldata->lifetime); // 시간 0.1 ~ 0.2 추가
														  //m_bullObj->SetIsFirstCreate(true);

														  //불렛이 처음생성됐을 때의 시간을 저장. 이후 해당 이벤트마다 이 불렛의 생성주기시간을 더해줌
		__int64 currTime; QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
		m_bullObj->m_prevTime = currTime;

		m_bullobjs.emplace_back(m_bullObj);

		STC_Attack stc_attack;
		stc_attack.bull_data = move(m_bullObj->GetBulletInfo());
		stc_attack.lifetime = m_bullObj->GetBulletLifeTime();

		//불렛을 쏜 캐릭터의 공격애니메이션을 다른 클라이언트에게도 보내준다
		STC_CharAnimation stc_charani;
		stc_charani.id = m_bullObj->GetBulletMasterID();
		stc_charani.char_animation = Ani_State::Attack;

		//불렛이 생성된 위치를 나 말고도 상대방도 알고 있어야함. //상대방 클라이언트에게 내 불렛 생성위치를 보냄
		for (auto client : m_clients)
		{
			//불렛을 쏜 클라이언트는 자신이 불렛을 생성했으므로 따로 생성정보를 보내주지 않아도됨 
			if (client->m_id == n_bldata->bull_data.Master_ID) continue;
			if (static_cast<bool>(client->m_pdata.ai) == true || static_cast<bool>(client->m_connect_state) == false) continue;

			client->SendPacket(reinterpret_cast<Packet*>(&stc_charani));
			client->SendPacket(reinterpret_cast<Packet*>(&stc_attack));
		}

		if (n_bldata->bull_data.type == BULLET_TYPE::protocol_LightBullet)
			g_timer_queue.AddEvent(n_bldata->bull_data.myID, 0, LIGHT_BULLET, true, n_bldata->bull_data.Master_ID);

		if (n_bldata->bull_data.type == BULLET_TYPE::protocol_HeavyBullet)
			g_timer_queue.AddEvent(n_bldata->bull_data.myID, 0, HEAVY_BULLET, true, n_bldata->bull_data.Master_ID);
	}
	break;

	case PACKET_PROTOCOL_TYPE::PLAYER_JUMP:
	{
		if (m_state == DEAD) break;

		auto jump_data = reinterpret_cast<STC_CharJump*>(packet);

		GeneratorJump j;
		j.SetJumpVel(XMFLOAT3(0, 100, 0));
		//j.Update(0.f, *pp);
		j.Update(0.f, *m_clients[jump_data->id]->GetPhysicsPoint());
		m_clients[jump_data->id]->m_pdata.airbone = true;
		//m_clients[jump_data->id]->AirBone = true;
		//m_pdata.airbone = true;
		//m_pdata.ani = jump_data.ani_state;
	}
	break;

	case PACKET_PROTOCOL_TYPE::TEST:
	{
		if (m_state == DEAD)
			break;

		auto test_data = reinterpret_cast<STC_Test*>(packet);

		cout << "ID: " << test_data->player_data.id << "ElaspedTime: " << test_data->time.t_time << "------"
			"PrevTime: " << test_data->time.p_time << endl;

	}
	break;

	}
}

void CPlayerObject::GravitySystem(double deltime)
{
	GeneratorGravity gg;
	gg.SetGravityAccel(XMFLOAT3(0, -100, 0));

	if (m_fixed == false)
	{
		gg.Update(deltime, *pp);
	}
}

void CPlayerObject::Tick(double deltime)
{
	XMFLOAT4 xmf4_pos{ m_pos4f.x, m_pos4f.y, m_pos4f.z, m_pos4f.w };
	pp->integrate(deltime, &xmf4_pos);
	m_pos4f.x = xmf4_pos.x; m_pos4f.y = xmf4_pos.y; 
	m_pos4f.y = xmf4_pos.y; m_pos4f.w = xmf4_pos.w;
}

void CPlayerObject::AfterGravitySystem(double deltime)
{
	float ppy = pp->GetPosition().y;
	float hby = pp->GetHalfBox().y;
	if (ppy - hby < 0)
	{
		XMFLOAT3 gp = pp->GetPosition();
		gp.y += hby - ppy;
		pp->SetPosition(gp);
		UpdatePPosCenterPos();
		auto v = pp->GetVelocity();
		v.y = 0;
		pp->SetVelocity(v);
		m_airbone = false;
	}
}

void CPlayerObject::Damaged(float damage)
{

}
