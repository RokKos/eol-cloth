//#include "../main.cpp"

#include "EOLLayer.h"
#include "../Core/Application.h"

namespace EOL {

	class EOLApplication : public Core::Application
	{
	public:
		EOLApplication()
		{
			PushLayer(new EOLLayer());
		}

		~EOLApplication()
		{
		}
	};

	

}

namespace Core {
	Application* CreateApplication() {
		return new EOL::EOLApplication();
	}
}