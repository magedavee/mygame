#include <string>
#include <stdint.h>
#include "Attributes.h"
#include "Graphics.h"
#include <iostream>
//#define DEBUG false||DEBUG_ALL

bool Graphics::DEBUG = false;

Graphics::Graphics()
{
/*	glutInit( &argc, args );
	 //Create OpenGL 2.1 context
        glutInitContextVersion( 2, 1 );

        //Create Double Buffered Window
        glutInitDisplayMode( GLUT_DOUBLE );
        glutInitWindowSize( SCREENWIDTH, SCREENHEIGHT );
        glutCreateWindow( "OpenGL" );
*/
	DEBUG=Game::DEBUG_GRAPHICS||Game::DEBUG_ALL;
	if(DEBUG)
		cout<<"DEBUG is on in Graphics\n";
	GLuint gVertexBuffer = 0;
	if(!this->init())
        {
                std::cout<<"failed init of graphics.\n";
        }
        else
        {
                if(DEBUG)
                std::cout<<"graphics ok\n";
        }
	void EnableTransparency();
}

Graphics::~Graphics()
{
}


bool Graphics::init()
{
	if(DEBUG)
		std::cout<<"initlizing Graphics\n";
     	if( SDL_Init(SDL_INIT_VIDEO)<0)
        {
                std::cout<<"sdl init fail\n";
                return false;
        }
     
    
   
       // screen = SDL_SetVideoMode( SCREENWIDTH, SCREENHEIGHT, SCREENBPP, SDL_OPENGL );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
//	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	screen =SDL_CreateWindow( "My Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );

        if(this->screen==NULL)
        {
                std::cout<<"screen null SDL Error: "<<SDL_GetError()<<endl;
                return false;
        }
  //Initialize PNG loading

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
	{ 
		std::cout<< "SDL_image could not initialize! SDL_image Error: "<< IMG_GetError() <<endl; 
		return false; 
	}
	else
	{
		if(DEBUG)
		{
			std::cout<<"Image Flags: "<<imgFlags<<endl; 
		}
	}	
	context= SDL_GL_CreateContext(screen);
	if(context==NULL)
	{
		cout<<"OpenGL context could not be created SDL Error:"<<SDL_GetError()<<endl;
		return false;
	}
	if( SDL_GL_SetSwapInterval( 1 ) < 0 )
	{
		cout<<"Warning Unable to set VSync:"<<SDL_GetError()<<endl;
	}
	//Initialize OpenGL 
	if(DEBUG)
		std::cout<<"initlizing OpenGL\n";
	if( initGL() == false ) 
	{
		std::cout<<"error with opengl\n";
		return false; 
	}
	
	if(DEBUG)
		std::cout<<"Finish with initilizing graphics\n";
  
        return true;
}

bool Graphics::initGL()
{
	GLenum glewError = glewInit();
	if( glewError != GLEW_OK )
	{
	    printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
	    return false;
	}
	if( !GLEW_VERSION_2_1 )
	{
	    printf( "OpenGL 2.1 not supported!\n" );
	    return false;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( 0.0, SCREENWIDTH, SCREENHEIGHT, 0.0, 1.0, -1.0 );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glEnable( GL_TEXTURE_2D );
	GLenum error=glGetError();
	if(error!=GL_NO_ERROR)
	{
		std::cout<<"error with open gl init\n";
		return false;
	}
	return true;
}

void Graphics::render()
{
	if(DEBUG)
	    std::cout<<"Render\n"; 
	    //Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );
/*	glEnableClientState( GL_VERTEX_ARRAY );
		//Set vertex data
        	glVertexPointer( 2, GL_FLOAT, 0, gQuadVertices );

        	//Draw quad using vertex data
        	glDrawArrays( GL_QUADS, 0, 4 );
	glDisableClientState( GL_VERTEX_ARRAY );*/
	    glLoadIdentity();
	//Move to center of the screen 
	//Render quad
	    glTranslatef( SCREENWIDTH / 2.f, SCREENHEIGHT / 2.f, 0.f );
	    glBegin( GL_QUADS );
	    glTexCoord2f(.25, .25);
	    glVertex2f( -250.f, -250.f );
	    glTexCoord2f(.75, .25);
	    glVertex2f(  250.f, -250.f );
	    glTexCoord2f(.75, .75);
	    glVertex2f(  250.f,  250.f );
	    glTexCoord2f(.25,.75);
	    glVertex2f( -250.f,  250.f );
	    glEnd();

	    //Update screen
	    SDL_GL_SwapWindow( screen );
}	



Texture* Graphics::loadTexture(std::string filename)
{
	if(DEBUG)
		std::cout<<"loading texture "<<filename.c_str()<<endl;
	Texture * texture=new Texture();
        SDL_Surface* surface = IMG_Load(filename.c_str());

        if (!surface) {

		std::cout<<"surface not loaded "<<filename<<" SDL image Error:"<<IMG_GetError()<<endl;
                return NULL;

        }
        int bpp=surface->format->BytesPerPixel;
	texture->setBPP(bpp);
	int mode=0;
        // work out what format to tell glTexImage2D to use...
        if (surface->format->BytesPerPixel == 3) { // RGB 24bit
			mode=GL_RGB;

        } else if (surface->format->BytesPerPixel == 4) { // RGBA 32bit

                mode=GL_RGBA;

        } else {

                SDL_FreeSurface(surface);
		std::cout<<"format error "<<filename<<endl;
                return NULL;

        }

	texture->setMode(mode);
        texture->setWidth(surface->w);
        texture->setHeight(surface->h);
	GLuint size=texture->getSize();	
	GLuint * mPixels=new GLuint[size];
  //      SDL_LockSurface(surface);
	
	for(int y=0;y<surface->h;++y)
	{
		for(int x=0;x<surface->w;++x)
		{
			int index=x+y*surface->w;
			mPixels[index]=getPixel(surface,x,y);
		}
	}
        // create one texture name
	GLuint textureID;
        glGenTextures(1, &textureID);
	texture->setID(textureID);

        // these affect how this texture is drawn later on...
	SDL_FreeSurface(surface);
	if(texture==NULL)
	{
		std::cout<<"texture failed to load";
	}
	bindTexture(texture);
	if(DEBUG)
		std::cout<<"pixels address: "<<mPixels<<endl;
	if(DEBUG)
		std::cout<<"glTexImage"<<endl;
	int w=texture->getWidth();
	int h=texture->getHeight();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);
        // these affect how this texture is drawn later on...
	if(DEBUG)
		std::cout<<"Texture Parameters"<<endl;
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	if(DEBUG)
		std::cout<<"Binding over"<<endl;
//	glBindTexture( GL_TEXTURE_2D, NULL ); 
	//Check for error 
	GLenum error = glGetError(); 
	if( error != GL_NO_ERROR ) 
	{ 
		cout<< "Error loading texture" <<gluErrorString( error )<<endl;
	} 
	if(DEBUG)
		std::cout<<"texture:  "<<texture<<endl;
	unbindTexture();
	texture->setPixels(mPixels);
	//delete mPixels;
	return texture;
        // tell opengl to use the generated texture name

}

void Graphics::unbindTexture()
{
        glBindTexture(GL_TEXTURE_2D, NULL);
}

void Graphics::bindTexture(Texture * texture)
{
	GLuint textureID=texture->getID();
	if(DEBUG)
		std::cout<<"now binding"<<endl;
        glBindTexture(GL_TEXTURE_2D, textureID);

}
void Graphics::freeTexture(Texture *texture)
{
	GLuint textureID=texture->getID();
        //Delete texture
        if( textureID != 0 )
        {
		glDeleteTextures( 1, &textureID );
		texture->setID(0);
        }

        texture->setWidth(0);
        texture->setHeight(0);
}

Uint32 Graphics::getPixel(SDL_Surface *surface, int x,int y)
{
	int bpp=0;
	if(x>=0&&y>=0&&x<surface->w&&y<surface->h)
	{
		bpp=surface->format->BytesPerPixel;
	}
	else
	{
		std::cout<<"x= "<<x<<" y ="<<y<<" is out of bounds\n";
		return 0;
	}
	Uint8 *p=(Uint8*)surface->pixels+y*surface->pitch+x*bpp;
	switch(bpp) 
	{
	    case 1:
		return *p;
		break;

	    case 2:
		return *(Uint16 *)p;
		break;

	    case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		    return p[0] << 16 | p[1] << 8 | p[2];
		else
		    return p[0] | p[1] << 8 | p[2] << 16;
		break;

	    case 4:
		return *(Uint32 *)p;
		break;

	    default:
		std::cout<<"Error in reading pixel at x="<<x<<" y="<<y<<endl;
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}



bool Graphics::updateTexture(Texture* texture)
{
	if(DEBUG)
		cout<<"unlock"<<endl;
	GLuint *mPixels= texture->getPixels();
	int mTextureWidth=texture->getWidth();
	int mTextureHeight=texture->getHeight();
	int mTextureID=texture->getID(); 
	//If texture is locked and a texture exists 
	if( mPixels != NULL && mTextureID != 0 ) 
	{ 
		//Set current texture 
		glBindTexture( GL_TEXTURE_2D, mTextureID ); 
		//Update texture 
		glTexSubImage2D( GL_TEXTURE_2D, 0, 0, 0, mTextureWidth, mTextureHeight, GL_RGBA, GL_UNSIGNED_BYTE, mPixels ); 
		//Unbind texture 
		unbindTexture();
		return true; 
	}
	return false;
}

void Graphics::addTexture(Texture *texture,Rects *clip)
{

}
