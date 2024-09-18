#include "memory/memory.h"
#include <iostream>
#include "offsets.hpp"
#include <thread>

using namespace std;

int main()
{
	const auto mem = Memory("cs2.exe");
	const auto client = mem.GetModuleAddress("client.dll");

	const auto jump = client + offsets::jump;

	while (true)
	{
		const uintptr_t dwLocalPlayerPawn = mem.Read<uintptr_t>(client + offsets::dwLocalPlayerPawn);

		if (!dwLocalPlayerPawn)
		{
			continue;
		}

		const uint32_t m_fFlags = mem.Read<uint32_t>(dwLocalPlayerPawn + offsets::m_fFlags);

		if (GetAsyncKeyState(VK_SPACE))
		{
			if (m_fFlags == 65665 || m_fFlags == 65667)
			{
				this_thread::sleep_for(chrono::milliseconds(1));
				mem.Write<uint32_t>(jump, 65537);
			}
			else
			{
				mem.Write<uint32_t>(jump, 256);
			}
		}

		this_thread::sleep_for(chrono::milliseconds(1));
	}

	return 0;
}
