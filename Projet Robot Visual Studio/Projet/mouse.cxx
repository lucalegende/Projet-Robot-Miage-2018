// $Id: mouse.cpp,v 1.1 2003/05/06 03:32:35 bush Exp $
// Written by:
//      Grant Macklem (Grant.Macklem@colorado.edu)
//      Gregory Schmelter (Gregory.Schmelter@colorado.edu)
//      Alan Schmidt (Alan.Schmidt@colorado.edu)
//      Ivan Stashak (Ivan.Stashak@colorado.edu)
// CSCI 4830/7818: API Programming
// University of Colorado at Boulder, Spring 2003
// http://www.cs.colorado.edu/~main/bgi
//


#include <windows.h>        // Provides Win32 API
#include <windowsx.h>       // Provides GDI helper macros
#include "winbgi.h"         // API routines
#include "winbgitypes.h"    // Internal structure data

/*****************************************************************************
*
*   Helper functions
*
*****************************************************************************/
// This function tests whether a given kind of mouse event is in range
// MGM: Added static to prevent linker conflicts
static bool MouseKindInRange( int kind )
{
    return ( (kind >= WM_MOUSEFIRST) && (kind <= WM_MOUSELAST) );
}

class eventmouse_queue {
private:
	int d_maxsize;
	int d_put, d_get;
	int *d_bufx, *d_bufy;
public:
	eventmouse_queue(int size = 256) : d_maxsize(size), d_put(0), d_get(0)
	{
		d_bufx = new int[d_maxsize]; d_bufy = new int[d_maxsize];
	}
	~eventmouse_queue()
	{
		delete[] d_bufx; delete[] d_bufy;
	}

	bool is_empty() const { return d_put == d_get; }
	void put(POINTS pt)
	{
		d_bufx[d_put] = pt.x; d_bufy[d_put] = pt.y;
		if (d_put == d_maxsize)  //no more place
			d_get = (d_get + 1) % d_maxsize;
		d_put = (d_put + 1) % d_maxsize;
	}
	void get(int& x, int& y)
	{
		x = d_bufx[d_get]; y = d_bufy[d_get];
		d_get = (d_get + 1) % d_maxsize;
	}
};

static eventmouse_queue mouse_queue;

/*****************************************************************************
*
*   The actual API calls are implemented below
*   MGM: Moved ismouseclick function to top to stop g++ 3.2.3 internal error.
*****************************************************************************/
bool ismouseclick( int kind )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );
    return ( MouseKindInRange( kind ) && pWndData->clicks[kind - WM_MOUSEFIRST].size( ) );
}

void clearmouseclick( int kind )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );

    // Clear the mouse event
    if ( MouseKindInRange( kind ) && pWndData->clicks[kind - WM_MOUSEFIRST].size( ) )
        pWndData->clicks[kind - WM_MOUSEFIRST].pop( );
}

void getmouseclick( int kind, int& x, int& y )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );
    POINTS where; // POINT (short) to tell where mouse event happened.
    
    // Check if mouse event is in range
    if ( !MouseKindInRange( kind ) )
        return;

    // Set position variables to mouse location, or to NO_CLICK if no event occured
    if ( MouseKindInRange( kind ) && pWndData->clicks[kind - WM_MOUSEFIRST].size( ) )
    {
	where = pWndData->clicks[kind - WM_MOUSEFIRST].front( );
        pWndData->clicks[kind - WM_MOUSEFIRST].pop( );
        x = where.x;
        y = where.y;
    }
    else
    {
        x = y = NO_CLICK;
    }
}

static bool handle_input(bool wait = false)
{
	MSG lpMsg;
	if (wait ? GetMessage(&lpMsg, NULL, 0, 0)
		: PeekMessage(&lpMsg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
		return true;
	}
	return false;
}

void getmouse(int& x, int& y)
{
	while (mouse_queue.is_empty()) handle_input(true);
	//    return (unsigned char)kbd_queue.get();  ???
	mouse_queue.get(x, y);
}

void setmousequeuestatus( int kind, bool status )
{
    if ( MouseKindInRange( kind ) )
	BGI__GetWindowDataPtr( )->mouse_queuing[kind - WM_MOUSEFIRST] = status;
}

// TODO: This may be viewport relative.  The documentation specifies with will range from 0 to getmaxx()
int mousex( )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );
    return pWndData->mouse.x;
}


// TODO: This may be viewport relative.  The documentation specifies with will range from 0 to getmaxy()
int mousey( )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );
    return pWndData->mouse.y;
}


void registermousehandler( int kind, void h( int, int ) )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );
    if ( MouseKindInRange( kind ) )
        pWndData->mouse_handlers[kind - WM_MOUSEFIRST] = h;
}
