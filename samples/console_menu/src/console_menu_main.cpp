//
// Included files.
//

//
// Platform specific definitions and overall build options for the library.
//
#include <guslib/guslibbuildopts.h>

// cout
#include <iostream>

#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
// kbhit
#include <conio.h>

// sleep
#include <Windows.h>
#endif  //  GUSLIB_PLATFORM_TYPE_WINDOWS

// console based menu - the main subject of this test.
#include "consolemenu.h"

using namespace std;
using namespace guslibsamples;

void displayInstructions()
{
  cout << "Enter single chars to interact" << endl
    << "List of char actions:" << endl
    << "` : see this message" << endl
    << "w : menu up" << endl
    << "s : menu down" << endl
    << "e : action (enter sub-menu, or enter/exit option edit mode)" << endl
    << "a : menu option previous value" << endl
    << "d : menu option next value" << endl
    << "q : go back to previous menu level" << endl
    << "x : exit the application" << endl;
}

class MyListener : public GMenuListener
{
public:
  MyListener() :GMenuListener() { bOver = false; }
  virtual ~MyListener() {}
  virtual void OnMenuAction(GMenuItem *item)
  {
    if (item->getName() == "exit")
    {
      bOver = true;
    }
  }
  virtual bool OnMenuBack(GMenuItem *item)
  {
    cout << "Back button pressed:" << item->getCaption() << endl;
    return true;
  }
  virtual void OnMenuShouldRedraw(GMenu * menu)
  {
  }
  virtual void OnMenuSelectionChange(GMenuItem *item)
  {
    cout << "menu selection changed for " << item->getCaption() << endl;
    cout << "new position is " << item->getSelectedChildIndex() << endl;
  }
  virtual void OnMenuDepthChange(GMenu * menu, bool fromTop)
  {
    if (menu == NULL)
    {
      cout << "Can't change depth; top level!" << endl;
    }
    else
    {
      cout << "Depth was changed, currently is " << menu->getActive()->getItemDepth()
        << " from " << (fromTop ? "top" : "bottom") << endl;
    }
  }
  virtual void OnMenuOptionValueChange(GMenuItem *optionGroup, GMenuItem *option)
  {
    cout << "Option for " << optionGroup->getName() << " changed to " << option->getName() << endl;
  }
  virtual void OnMenuOptionStartEdit(GMenuItem *optionGroup, GMenuItem *option)
  {
    cout << "Started editing " << optionGroup->getName() << ", " << option->getName() << endl;
  }
  virtual void OnMenuOptionStopEdit(GMenuItem *optionGroup, GMenuItem *option, bool bCanceled)
  {
    cout << (bCanceled ? "Cancelled" : "Accepted") << " option change for " << optionGroup->getName() << ", " << option->getName() << endl;
  }

  bool bOver;
};


void drawMenu(GMenu *menu)
{
  GMenuItemList vect = menu->getVisible()->getChildren();
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
  std::system("cls");
#endif  //  GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
  cout << "--------------" << menu->getVisible()->getCaption() << "------------ (Press [`] for help)" << endl;
  for (GMenuItemList::iterator it = vect.begin(); it != vect.end(); ++it)
  {
    if ((*it)->isSelected())
    {
      cout << "(X)" << (*it)->getCaption() << "; type=" << (*it)->getType() << "... lvl=" << (*it)->getItemDepth();
    }
    else
    {
      cout << "( )" << (*it)->getCaption() << "; type=" << (*it)->getType();
    }
    if ((*it) == menu->getActive())
    {
      cout << "(option edit, press left-right cmd)";
    }
    cout << endl;
  }
}

void menutest()
{
  GMenu * myMenu = new GMenu();

  GMenuAction *quick = new GMenuAction(myMenu, "quick", "Quick game");
  //myMenu->getRoot()->addSubItem( quick );
  GMenuSubMenu *sub1 = new GMenuSubMenu(myMenu, "game", "Game");
  GMenuAction *ac1 = new GMenuAction(myMenu, "map1", "Map 1");
  GMenuAction *ac2 = new GMenuAction(myMenu, "map2", "Map 2");
  GMenuBack *ac3 = new GMenuBack(myMenu, "bk1", "Back__");
  sub1->addChild(ac1);
  sub1->addChild(ac2);
  sub1->addChild(ac3);
  GMenuSubMenu *sub2 = new GMenuSubMenu(myMenu, "options", "Options");
  GMenuOption *op1 = new GMenuOption(myMenu, "resolution", "Resolution");
  GMenuItem *v1 = new GMenuItem(myMenu, "v1", "800x600");
  GMenuItem *v2 = new GMenuItem(myMenu, "v2", "1024x768");
  GMenuItem *v3 = new GMenuItem(myMenu, "v3", "1280x1024");
  op1->addChild(v1);
  op1->addChild(v2);
  op1->addChild(v3);
  GMenuOption *op5 = new GMenuOption(myMenu, "engine", "Engine");
  v1 = new GMenuItem(myMenu, "v1.1", "Direct3D");
  v2 = new GMenuItem(myMenu, "v2.1", "OpenGL");
  op5->addChild(v1);
  op5->addChild(v2);

  GMenuOption *op2 = new GMenuOption(myMenu, "shadows", "Shadows");
  v1 = new GMenuItem(myMenu, "v1", "On");
  v2 = new GMenuItem(myMenu, "v2", "Off");
  op2->addChild(v1);
  op2->addChild(v2);
  sub2->addChild(op5);
  sub2->addChild(op1);
  sub2->addChild(op2);

  myMenu->getRoot()->addChild(sub1);
  myMenu->getRoot()->addChild(sub2);
  myMenu->getRoot()->addChild(quick);
  myMenu->getRoot()->setSelectionWrapping(true);

  GMenuAction *ex = new GMenuAction(myMenu, "exit", "Exit");
  myMenu->getRoot()->addChild(ex);

  MyListener *lst = new MyListener();
  myMenu->setListener(lst);

  GMenuItem * myItem = myMenu->searchForItemByName("quick");
  if (myItem == NULL)
  {
    cout << "problem: existent item not found quick!" << endl;
  }
  myItem = myMenu->searchForItemByName("v1");
  if (myItem == NULL)
  {
    cout << "problem: existent item not found v1!" << endl;
  }
  myItem = myMenu->searchForItemByName("inexistent");
  if (myItem != NULL)
  {
    cout << "problem: inexistent item found!" << endl;
  }
  cout << "Give nums, [0] to quit ([40]=btm, [38]=top, [37]=left, [39]=right, [13]=select, [27]=back)" << endl;

  myMenu->setKeyMap(GMenuCommand::cmdMenuUp, 'w');
  myMenu->setKeyMap(GMenuCommand::cmdMenuDown, 's');
  myMenu->setKeyMap(GMenuCommand::cmdActionLeft, 'a');
  myMenu->setKeyMap(GMenuCommand::cmdActionRight, 'd');
  myMenu->setKeyMap(GMenuCommand::cmdActionIn, 'e');
  myMenu->setKeyMap(GMenuCommand::cmdActionEsc, 'q');
  //int allowedKeys[] = {40, 38, 37, 39, 13, 27};
  //int nNumAllowedKeys = 6;
  bool bOver = false;
  drawMenu(myMenu);

  while (!bOver)
  {
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
    while (!_kbhit())
    {
      ::Sleep(17);
    }
#endif
    char c;
#if GUSLIB_PLATFORM_TYPE == GUSLIB_PLATFORM_TYPE_WINDOWS
    c = _getch();
#else
    c = getchar();
#endif
    if (c == 'x')
    {
      bOver = true;
    }
    else if (c == '`')
    {
      displayInstructions();
    }
    else
    {
      myMenu->reactToKeyPress(c);
      bOver = lst->bOver;
      drawMenu(myMenu);
    }


    //int n;
    //scanf("%d", &n);
    //{
    //	myMenu->reactToKeyPress(n);
    //	bool bFound = false;
    //	for( int i=0; i<6; i++ ) if( n==allowedKeys[i] ) bFound = true;
    //	bOver = !bFound || lst->bOver;
    //	drawMenu(myMenu);
    //}
  }
}

int main()
{
  menutest();

  cout << "done" << endl;

  return 0;
}