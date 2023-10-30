
#include "application.h"	

/*


AUTHOR--
RADEK ŠMIGA
SMI0132

*/
// Key states

int main(void)
{
	application* app = new application();
	app->init();

	 //Loading scene
    //app->createShaders();   
    app->createScenes();
    app->run(); //Rendering 
	delete(app);
}