#include <qimage.h>
#include <qgl.h>

class texture
{
	private:
		QImage texture;
		unsigned int texId;
	public:
		bool loadImage( QString path );

		int getWidth();
		int getHeight();

		int getTexture();

};
