
#include <main.hpp>

int main(int argc, char *argv[])
{
	boost::shared_ptr<iq::app> app;

	std::cout.setf(std::ios::unitbuf);

	try
	{
		app.reset(new iq::app(argc, argv));

/*
 * h4x: testing animation.
 */
boost::shared_ptr<BITMAP> bitmap;
boost::shared_ptr<iq::entity> intern(new iq::entity("config/intern.xml"));
int x, y;

intern->begin_animation("walk_down", app->ms);

x = (app->scrbuf->w / 2) - (intern->w / 2);
y = (app->scrbuf->h / 2) - (intern->h / 2);

		// Main game loop.
		while(!(key[KEY_Q] || key[KEY_ESC] || iq::app::close_button_pressed))
		{
			// Sleep until next frame.
			sem_wait(app->sem.get());

			// Logic loop. Changes to the game happen here.
			app->logic();

for(int i=0; i<3; i++)
{
	hline(app->scrbuf.get(), 0, app->scrbuf->h / 2 - 1 + i, app->scrbuf->w, makecol(155, 0, 0));
	vline(app->scrbuf.get(), app->scrbuf->w / 2 - 1 + i, 0, app->scrbuf->h, makecol(155, 0, 0));
	rect(app->scrbuf.get(), 0+i, 0+i, app->scrbuf->w - 1 - i, app->scrbuf->h - 1 - i, makecol(155, 0, 0));
}

/*
 * h4x: testing animation.
 */
bitmap = intern->current_frame(app->ms);
masked_blit(bitmap.get(), app->scrbuf.get(), 0, 0, x, y, bitmap->w, bitmap->h);

			/*
			 * Draw. Here we draw the current frame first to a buffer in main
			 * memory and then to the video memory (screen).
			 */
			app->draw();
		}
	}
	catch(std::invalid_argument &ex)
	{
		printf("An invalid argument was passed: %s\n", ex.what());
		allegro_message("An invalid argument was passed: %s\n", ex.what());
	}
	catch(std::range_error &ex)
	{
		printf("A range error occurred: %s\n", ex.what());
		allegro_message("A range error occurred: %s\n", ex.what());
	}
	catch(std::logic_error &ex)
	{
		printf("A logic error occurred: %s\n", ex.what());
		allegro_message("A logic error occurred: %s\n", ex.what());
	}
	catch(std::runtime_error &ex)
	{
		printf("A runtime error occurred: %s\n", ex.what());
		allegro_message("A runtime error occurred: %s\n", ex.what());
	}
	catch(std::exception &ex)
	{
		printf("An exception occurred: %s\n", ex.what());
		allegro_message("An exception occurred: %s\n", ex.what());
	}

	return(0);
}
END_OF_MAIN()



//void tick(void)
//{
//	g_seconds++;
//	g_frames_per_second = g_frames_this_second;
//	g_frames_this_second = 0;
//}
//END_OF_FUNCTION(tick)

