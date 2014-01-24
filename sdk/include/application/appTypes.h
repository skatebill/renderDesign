#pragma once
namespace xc{
	namespace app{
		enum EnumEventType{
			Event_Mouse,
			Event_Key,
			Event_Touch
		};
		enum EnumMouse{
			Mouse_L,
			Mouse_R,
			Mouse_M
		};
		enum MouseEvent{
			Mouse_Click,
			Mouse_Down,
			Mouse_Up,
			Mouse_DClick
		};
		enum KeyEvent
		{
			Key_Down,
			Key_Up
		};
	}
}