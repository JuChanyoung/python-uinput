#include <Python.h>

#include "suinput.h"

/*
  TODO: Provide more "Pythonic" API. Create for example a file-like type for
  input driver.
*/

static PyObject* cUinput_open(PyObject *self, PyObject *args)
{
  /* TODO: name + id stuff as arguments */
  struct input_id id = {BUS_BLUETOOTH, 1, 2, 3};
  int uinput_fd = suinput_open("python-cUinput", &id);
  if (uinput_fd == -1)
    return PyErr_SetFromErrno(PyExc_IOError);
  return Py_BuildValue("i", uinput_fd);
}

static PyObject* cUinput_close(PyObject *self, PyObject *args)
{
  int uinput_fd;
  if (!PyArg_ParseTuple(args, "i", &uinput_fd))
    return NULL;
  if (suinput_close(uinput_fd) == -1)
    return PyErr_SetFromErrno(PyExc_IOError);
  Py_RETURN_NONE;
}

static PyObject* cUinput_press(PyObject *self, PyObject *args)
{
  int uinput_fd;
  uint16_t code;
  if (!PyArg_ParseTuple(args, "iH", &uinput_fd, &code))
    return NULL;
  if (suinput_press(uinput_fd, code) == -1)
    return PyErr_SetFromErrno(PyExc_IOError);
  Py_RETURN_NONE;
}

static PyObject* cUinput_release(PyObject *self, PyObject *args)
{
  int uinput_fd;
  uint16_t code;
  if (!PyArg_ParseTuple(args, "iH", &uinput_fd, &code))
    return NULL;
  if (suinput_release(uinput_fd, code) == -1)
    return PyErr_SetFromErrno(PyExc_IOError);
  Py_RETURN_NONE;
}

static PyObject* cUinput_click(PyObject *self, PyObject *args)
{
  int uinput_fd;
  uint16_t code;
  if (!PyArg_ParseTuple(args, "iH", &uinput_fd, &code))
    return NULL;
  if (suinput_click(uinput_fd, code) == -1)
    return PyErr_SetFromErrno(PyExc_IOError);
  Py_RETURN_NONE;
}

static PyObject* cUinput_move_pointer(PyObject *self, PyObject *args)
{
  int uinput_fd;
  int32_t x;
  int32_t y;
  if (!PyArg_ParseTuple(args, "iii", &uinput_fd, &x, &y)) {
    return NULL;
  }
  if (suinput_move_pointer(uinput_fd, x, y) == -1)
    return PyErr_SetFromErrno(PyExc_IOError);
  Py_RETURN_NONE;
}

static PyMethodDef cUinputMethods[] = {
  {"open", cUinput_open, METH_NOARGS,
   "open()\n\n"
   "Creates and opens a connection to the event device. Returns uinput\n"
   "file descriptor."},

  {"close", cUinput_close, METH_VARARGS,
   "close(uinput_fd)\n\n"
   "Destroys and closes a connection to the event device."},

  {"click", cUinput_click, METH_VARARGS,
   "click(uinput_fd, btn|key)\n\n"
   "Sends a button/key press and release events to the event device."},

  {"press", cUinput_press, METH_VARARGS,
   "press(uinput_fd, btn|key)\n\n"
   "Sends a button/key press event to the event device."},

  {"release", cUinput_release, METH_VARARGS,
   "release(uinput_fd, btn|key)\n\n"
   "Sends a button/key release event to the event device."},

  {"move_pointer", cUinput_move_pointer, METH_VARARGS,
   "move_pointer(uinput_fd, x, y)\n\n"
   "Sends a relative pointer motion event to the event device. Values\n"
   "increase towards right-bottom."},

  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC initcUinput(void)
{
  PyObject* module;
  module = Py_InitModule3("cUinput", cUinputMethods,
                          "User space input driver interface.\n\n"
                          "Provides a high-level API for the Linux input subsystem through the user\n"
                          "space event device.\n\n"
                          "KEY_*/BTN_* codes are Linux kernel key and button codes\n"
                          "defined in linux/input.h");
  PyModule_AddIntMacro(module, KEY_RESERVED);
  PyModule_AddIntMacro(module, KEY_ESC);
  PyModule_AddIntMacro(module, KEY_1);
  PyModule_AddIntMacro(module, KEY_2);
  PyModule_AddIntMacro(module, KEY_3);
  PyModule_AddIntMacro(module, KEY_4);
  PyModule_AddIntMacro(module, KEY_5);
  PyModule_AddIntMacro(module, KEY_6);
  PyModule_AddIntMacro(module, KEY_7);
  PyModule_AddIntMacro(module, KEY_8);
  PyModule_AddIntMacro(module, KEY_9);
  PyModule_AddIntMacro(module, KEY_0);
  PyModule_AddIntMacro(module, KEY_MINUS);
  PyModule_AddIntMacro(module, KEY_EQUAL);
  PyModule_AddIntMacro(module, KEY_BACKSPACE);
  PyModule_AddIntMacro(module, KEY_TAB);
  PyModule_AddIntMacro(module, KEY_Q);
  PyModule_AddIntMacro(module, KEY_W);
  PyModule_AddIntMacro(module, KEY_E);
  PyModule_AddIntMacro(module, KEY_R);
  PyModule_AddIntMacro(module, KEY_T);
  PyModule_AddIntMacro(module, KEY_Y);
  PyModule_AddIntMacro(module, KEY_U);
  PyModule_AddIntMacro(module, KEY_I);
  PyModule_AddIntMacro(module, KEY_O);
  PyModule_AddIntMacro(module, KEY_P);
  PyModule_AddIntMacro(module, KEY_LEFTBRACE);
  PyModule_AddIntMacro(module, KEY_RIGHTBRACE);
  PyModule_AddIntMacro(module, KEY_ENTER);
  PyModule_AddIntMacro(module, KEY_LEFTCTRL);
  PyModule_AddIntMacro(module, KEY_A);
  PyModule_AddIntMacro(module, KEY_S);
  PyModule_AddIntMacro(module, KEY_D);
  PyModule_AddIntMacro(module, KEY_F);
  PyModule_AddIntMacro(module, KEY_G);
  PyModule_AddIntMacro(module, KEY_H);
  PyModule_AddIntMacro(module, KEY_J);
  PyModule_AddIntMacro(module, KEY_K);
  PyModule_AddIntMacro(module, KEY_L);
  PyModule_AddIntMacro(module, KEY_SEMICOLON);
  PyModule_AddIntMacro(module, KEY_APOSTROPHE);
  PyModule_AddIntMacro(module, KEY_GRAVE);
  PyModule_AddIntMacro(module, KEY_LEFTSHIFT);
  PyModule_AddIntMacro(module, KEY_BACKSLASH);
  PyModule_AddIntMacro(module, KEY_Z);
  PyModule_AddIntMacro(module, KEY_X);
  PyModule_AddIntMacro(module, KEY_C);
  PyModule_AddIntMacro(module, KEY_V);
  PyModule_AddIntMacro(module, KEY_B);
  PyModule_AddIntMacro(module, KEY_N);
  PyModule_AddIntMacro(module, KEY_M);
  PyModule_AddIntMacro(module, KEY_COMMA);
  PyModule_AddIntMacro(module, KEY_DOT);
  PyModule_AddIntMacro(module, KEY_SLASH);
  PyModule_AddIntMacro(module, KEY_RIGHTSHIFT);
  PyModule_AddIntMacro(module, KEY_KPASTERISK);
  PyModule_AddIntMacro(module, KEY_LEFTALT);
  PyModule_AddIntMacro(module, KEY_SPACE);
  PyModule_AddIntMacro(module, KEY_CAPSLOCK);
  PyModule_AddIntMacro(module, KEY_F1);
  PyModule_AddIntMacro(module, KEY_F2);
  PyModule_AddIntMacro(module, KEY_F3);
  PyModule_AddIntMacro(module, KEY_F4);
  PyModule_AddIntMacro(module, KEY_F5);
  PyModule_AddIntMacro(module, KEY_F6);
  PyModule_AddIntMacro(module, KEY_F7);
  PyModule_AddIntMacro(module, KEY_F8);
  PyModule_AddIntMacro(module, KEY_F9);
  PyModule_AddIntMacro(module, KEY_F10);
  PyModule_AddIntMacro(module, KEY_NUMLOCK);
  PyModule_AddIntMacro(module, KEY_SCROLLLOCK);
  PyModule_AddIntMacro(module, KEY_KP7);
  PyModule_AddIntMacro(module, KEY_KP8);
  PyModule_AddIntMacro(module, KEY_KP9);
  PyModule_AddIntMacro(module, KEY_KPMINUS);
  PyModule_AddIntMacro(module, KEY_KP4);
  PyModule_AddIntMacro(module, KEY_KP5);
  PyModule_AddIntMacro(module, KEY_KP6);
  PyModule_AddIntMacro(module, KEY_KPPLUS);
  PyModule_AddIntMacro(module, KEY_KP1);
  PyModule_AddIntMacro(module, KEY_KP2);
  PyModule_AddIntMacro(module, KEY_KP3);
  PyModule_AddIntMacro(module, KEY_KP0);
  PyModule_AddIntMacro(module, KEY_KPDOT);
  PyModule_AddIntMacro(module, KEY_ZENKAKUHANKAKU);
  PyModule_AddIntMacro(module, KEY_102ND);
  PyModule_AddIntMacro(module, KEY_F11);
  PyModule_AddIntMacro(module, KEY_F12);
  PyModule_AddIntMacro(module, KEY_RO);
  PyModule_AddIntMacro(module, KEY_KATAKANA);
  PyModule_AddIntMacro(module, KEY_HIRAGANA);
  PyModule_AddIntMacro(module, KEY_HENKAN);
  PyModule_AddIntMacro(module, KEY_KATAKANAHIRAGANA);
  PyModule_AddIntMacro(module, KEY_MUHENKAN);
  PyModule_AddIntMacro(module, KEY_KPJPCOMMA);
  PyModule_AddIntMacro(module, KEY_KPENTER);
  PyModule_AddIntMacro(module, KEY_RIGHTCTRL);
  PyModule_AddIntMacro(module, KEY_KPSLASH);
  PyModule_AddIntMacro(module, KEY_SYSRQ);
  PyModule_AddIntMacro(module, KEY_RIGHTALT);
  PyModule_AddIntMacro(module, KEY_LINEFEED);
  PyModule_AddIntMacro(module, KEY_HOME);
  PyModule_AddIntMacro(module, KEY_UP);
  PyModule_AddIntMacro(module, KEY_PAGEUP);
  PyModule_AddIntMacro(module, KEY_LEFT);
  PyModule_AddIntMacro(module, KEY_RIGHT);
  PyModule_AddIntMacro(module, KEY_END);
  PyModule_AddIntMacro(module, KEY_DOWN);
  PyModule_AddIntMacro(module, KEY_PAGEDOWN);
  PyModule_AddIntMacro(module, KEY_INSERT);
  PyModule_AddIntMacro(module, KEY_DELETE);
  PyModule_AddIntMacro(module, KEY_MACRO);
  PyModule_AddIntMacro(module, KEY_MUTE);
  PyModule_AddIntMacro(module, KEY_VOLUMEDOWN);
  PyModule_AddIntMacro(module, KEY_VOLUMEUP);
  PyModule_AddIntMacro(module, KEY_POWER);
  PyModule_AddIntMacro(module, KEY_KPEQUAL);
  PyModule_AddIntMacro(module, KEY_KPPLUSMINUS);
  PyModule_AddIntMacro(module, KEY_PAUSE);
  PyModule_AddIntMacro(module, KEY_SCALE);
  PyModule_AddIntMacro(module, KEY_KPCOMMA);
  PyModule_AddIntMacro(module, KEY_HANGEUL);
  PyModule_AddIntMacro(module, KEY_HANGUEL);
  PyModule_AddIntMacro(module, KEY_HANJA);
  PyModule_AddIntMacro(module, KEY_YEN);
  PyModule_AddIntMacro(module, KEY_LEFTMETA);
  PyModule_AddIntMacro(module, KEY_RIGHTMETA);
  PyModule_AddIntMacro(module, KEY_COMPOSE);
  PyModule_AddIntMacro(module, KEY_STOP);
  PyModule_AddIntMacro(module, KEY_AGAIN);
  PyModule_AddIntMacro(module, KEY_PROPS);
  PyModule_AddIntMacro(module, KEY_UNDO);
  PyModule_AddIntMacro(module, KEY_FRONT);
  PyModule_AddIntMacro(module, KEY_COPY);
  PyModule_AddIntMacro(module, KEY_OPEN);
  PyModule_AddIntMacro(module, KEY_PASTE);
  PyModule_AddIntMacro(module, KEY_FIND);
  PyModule_AddIntMacro(module, KEY_CUT);
  PyModule_AddIntMacro(module, KEY_HELP);
  PyModule_AddIntMacro(module, KEY_MENU);
  PyModule_AddIntMacro(module, KEY_CALC);
  PyModule_AddIntMacro(module, KEY_SETUP);
  PyModule_AddIntMacro(module, KEY_SLEEP);
  PyModule_AddIntMacro(module, KEY_WAKEUP);
  PyModule_AddIntMacro(module, KEY_FILE);
  PyModule_AddIntMacro(module, KEY_SENDFILE);
  PyModule_AddIntMacro(module, KEY_DELETEFILE);
  PyModule_AddIntMacro(module, KEY_XFER);
  PyModule_AddIntMacro(module, KEY_PROG1);
  PyModule_AddIntMacro(module, KEY_PROG2);
  PyModule_AddIntMacro(module, KEY_WWW);
  PyModule_AddIntMacro(module, KEY_MSDOS);
  PyModule_AddIntMacro(module, KEY_COFFEE);
  PyModule_AddIntMacro(module, KEY_SCREENLOCK);
  PyModule_AddIntMacro(module, KEY_DIRECTION);
  PyModule_AddIntMacro(module, KEY_CYCLEWINDOWS);
  PyModule_AddIntMacro(module, KEY_MAIL);
  PyModule_AddIntMacro(module, KEY_BOOKMARKS);
  PyModule_AddIntMacro(module, KEY_COMPUTER);
  PyModule_AddIntMacro(module, KEY_BACK);
  PyModule_AddIntMacro(module, KEY_FORWARD);
  PyModule_AddIntMacro(module, KEY_CLOSECD);
  PyModule_AddIntMacro(module, KEY_EJECTCD);
  PyModule_AddIntMacro(module, KEY_EJECTCLOSECD);
  PyModule_AddIntMacro(module, KEY_NEXTSONG);
  PyModule_AddIntMacro(module, KEY_PLAYPAUSE);
  PyModule_AddIntMacro(module, KEY_PREVIOUSSONG);
  PyModule_AddIntMacro(module, KEY_STOPCD);
  PyModule_AddIntMacro(module, KEY_RECORD);
  PyModule_AddIntMacro(module, KEY_REWIND);
  PyModule_AddIntMacro(module, KEY_PHONE);
  PyModule_AddIntMacro(module, KEY_ISO);
  PyModule_AddIntMacro(module, KEY_CONFIG);
  PyModule_AddIntMacro(module, KEY_HOMEPAGE);
  PyModule_AddIntMacro(module, KEY_REFRESH);
  PyModule_AddIntMacro(module, KEY_EXIT);
  PyModule_AddIntMacro(module, KEY_MOVE);
  PyModule_AddIntMacro(module, KEY_EDIT);
  PyModule_AddIntMacro(module, KEY_SCROLLUP);
  PyModule_AddIntMacro(module, KEY_SCROLLDOWN);
  PyModule_AddIntMacro(module, KEY_KPLEFTPAREN);
  PyModule_AddIntMacro(module, KEY_KPRIGHTPAREN);
  PyModule_AddIntMacro(module, KEY_NEW);
  PyModule_AddIntMacro(module, KEY_REDO);
  PyModule_AddIntMacro(module, KEY_F13);
  PyModule_AddIntMacro(module, KEY_F14);
  PyModule_AddIntMacro(module, KEY_F15);
  PyModule_AddIntMacro(module, KEY_F16);
  PyModule_AddIntMacro(module, KEY_F17);
  PyModule_AddIntMacro(module, KEY_F18);
  PyModule_AddIntMacro(module, KEY_F19);
  PyModule_AddIntMacro(module, KEY_F20);
  PyModule_AddIntMacro(module, KEY_F21);
  PyModule_AddIntMacro(module, KEY_F22);
  PyModule_AddIntMacro(module, KEY_F23);
  PyModule_AddIntMacro(module, KEY_F24);
  PyModule_AddIntMacro(module, KEY_PLAYCD);
  PyModule_AddIntMacro(module, KEY_PAUSECD);
  PyModule_AddIntMacro(module, KEY_PROG3);
  PyModule_AddIntMacro(module, KEY_PROG4);
  PyModule_AddIntMacro(module, KEY_DASHBOARD);
  PyModule_AddIntMacro(module, KEY_SUSPEND);
  PyModule_AddIntMacro(module, KEY_CLOSE);
  PyModule_AddIntMacro(module, KEY_PLAY);
  PyModule_AddIntMacro(module, KEY_FASTFORWARD);
  PyModule_AddIntMacro(module, KEY_BASSBOOST);
  PyModule_AddIntMacro(module, KEY_PRINT);
  PyModule_AddIntMacro(module, KEY_HP);
  PyModule_AddIntMacro(module, KEY_CAMERA);
  PyModule_AddIntMacro(module, KEY_SOUND);
  PyModule_AddIntMacro(module, KEY_QUESTION);
  PyModule_AddIntMacro(module, KEY_EMAIL);
  PyModule_AddIntMacro(module, KEY_CHAT);
  PyModule_AddIntMacro(module, KEY_SEARCH);
  PyModule_AddIntMacro(module, KEY_CONNECT);
  PyModule_AddIntMacro(module, KEY_FINANCE);
  PyModule_AddIntMacro(module, KEY_SPORT);
  PyModule_AddIntMacro(module, KEY_SHOP);
  PyModule_AddIntMacro(module, KEY_ALTERASE);
  PyModule_AddIntMacro(module, KEY_CANCEL);
  PyModule_AddIntMacro(module, KEY_BRIGHTNESSDOWN);
  PyModule_AddIntMacro(module, KEY_BRIGHTNESSUP);
  PyModule_AddIntMacro(module, KEY_MEDIA);
  PyModule_AddIntMacro(module, KEY_SWITCHVIDEOMODE);
  PyModule_AddIntMacro(module, KEY_KBDILLUMTOGGLE);
  PyModule_AddIntMacro(module, KEY_KBDILLUMDOWN);
  PyModule_AddIntMacro(module, KEY_KBDILLUMUP);
  PyModule_AddIntMacro(module, KEY_SEND);
  PyModule_AddIntMacro(module, KEY_REPLY);
  PyModule_AddIntMacro(module, KEY_FORWARDMAIL);
  PyModule_AddIntMacro(module, KEY_SAVE);
  PyModule_AddIntMacro(module, KEY_DOCUMENTS);
  PyModule_AddIntMacro(module, KEY_BATTERY);
  PyModule_AddIntMacro(module, KEY_BLUETOOTH);
  PyModule_AddIntMacro(module, KEY_WLAN);
  PyModule_AddIntMacro(module, KEY_UWB);
  PyModule_AddIntMacro(module, KEY_UNKNOWN);
  PyModule_AddIntMacro(module, KEY_VIDEO_NEXT);
  PyModule_AddIntMacro(module, KEY_VIDEO_PREV);
  PyModule_AddIntMacro(module, KEY_BRIGHTNESS_CYCLE);
  PyModule_AddIntMacro(module, KEY_BRIGHTNESS_ZERO);
  PyModule_AddIntMacro(module, KEY_DISPLAY_OFF);
  PyModule_AddIntMacro(module, KEY_WIMAX);
  PyModule_AddIntMacro(module, BTN_MISC);
  PyModule_AddIntMacro(module, BTN_0);
  PyModule_AddIntMacro(module, BTN_1);
  PyModule_AddIntMacro(module, BTN_2);
  PyModule_AddIntMacro(module, BTN_3);
  PyModule_AddIntMacro(module, BTN_4);
  PyModule_AddIntMacro(module, BTN_5);
  PyModule_AddIntMacro(module, BTN_6);
  PyModule_AddIntMacro(module, BTN_7);
  PyModule_AddIntMacro(module, BTN_8);
  PyModule_AddIntMacro(module, BTN_9);
  PyModule_AddIntMacro(module, BTN_MOUSE);
  PyModule_AddIntMacro(module, BTN_LEFT);
  PyModule_AddIntMacro(module, BTN_RIGHT);
  PyModule_AddIntMacro(module, BTN_MIDDLE);
  PyModule_AddIntMacro(module, BTN_SIDE);
  PyModule_AddIntMacro(module, BTN_EXTRA);
  PyModule_AddIntMacro(module, BTN_FORWARD);
  PyModule_AddIntMacro(module, BTN_BACK);
  PyModule_AddIntMacro(module, BTN_TASK);
  PyModule_AddIntMacro(module, BTN_JOYSTICK);
  PyModule_AddIntMacro(module, BTN_TRIGGER);
  PyModule_AddIntMacro(module, BTN_THUMB);
  PyModule_AddIntMacro(module, BTN_THUMB2);
  PyModule_AddIntMacro(module, BTN_TOP);
  PyModule_AddIntMacro(module, BTN_TOP2);
  PyModule_AddIntMacro(module, BTN_PINKIE);
  PyModule_AddIntMacro(module, BTN_BASE);
  PyModule_AddIntMacro(module, BTN_BASE2);
  PyModule_AddIntMacro(module, BTN_BASE3);
  PyModule_AddIntMacro(module, BTN_BASE4);
  PyModule_AddIntMacro(module, BTN_BASE5);
  PyModule_AddIntMacro(module, BTN_BASE6);
  PyModule_AddIntMacro(module, BTN_DEAD);
  PyModule_AddIntMacro(module, BTN_GAMEPAD);
  PyModule_AddIntMacro(module, BTN_A);
  PyModule_AddIntMacro(module, BTN_B);
  PyModule_AddIntMacro(module, BTN_C);
  PyModule_AddIntMacro(module, BTN_X);
  PyModule_AddIntMacro(module, BTN_Y);
  PyModule_AddIntMacro(module, BTN_Z);
  PyModule_AddIntMacro(module, BTN_TL);
  PyModule_AddIntMacro(module, BTN_TR);
  PyModule_AddIntMacro(module, BTN_TL2);
  PyModule_AddIntMacro(module, BTN_TR2);
  PyModule_AddIntMacro(module, BTN_SELECT);
  PyModule_AddIntMacro(module, BTN_START);
  PyModule_AddIntMacro(module, BTN_MODE);
  PyModule_AddIntMacro(module, BTN_THUMBL);
  PyModule_AddIntMacro(module, BTN_THUMBR);
  PyModule_AddIntMacro(module, BTN_DIGI);
  PyModule_AddIntMacro(module, BTN_TOOL_PEN);
  PyModule_AddIntMacro(module, BTN_TOOL_RUBBER);
  PyModule_AddIntMacro(module, BTN_TOOL_BRUSH);
  PyModule_AddIntMacro(module, BTN_TOOL_PENCIL);
  PyModule_AddIntMacro(module, BTN_TOOL_AIRBRUSH);
  PyModule_AddIntMacro(module, BTN_TOOL_FINGER);
  PyModule_AddIntMacro(module, BTN_TOOL_MOUSE);
  PyModule_AddIntMacro(module, BTN_TOOL_LENS);
  PyModule_AddIntMacro(module, BTN_TOUCH);
  PyModule_AddIntMacro(module, BTN_STYLUS);
  PyModule_AddIntMacro(module, BTN_STYLUS2);
  PyModule_AddIntMacro(module, BTN_TOOL_DOUBLETAP);
  PyModule_AddIntMacro(module, BTN_TOOL_TRIPLETAP);
  PyModule_AddIntMacro(module, BTN_WHEEL);
  PyModule_AddIntMacro(module, BTN_GEAR_DOWN);
  PyModule_AddIntMacro(module, BTN_GEAR_UP);
  PyModule_AddIntMacro(module, KEY_OK);
  PyModule_AddIntMacro(module, KEY_SELECT);
  PyModule_AddIntMacro(module, KEY_GOTO);
  PyModule_AddIntMacro(module, KEY_CLEAR);
  PyModule_AddIntMacro(module, KEY_POWER2);
  PyModule_AddIntMacro(module, KEY_OPTION);
  PyModule_AddIntMacro(module, KEY_INFO);
  PyModule_AddIntMacro(module, KEY_TIME);
  PyModule_AddIntMacro(module, KEY_VENDOR);
  PyModule_AddIntMacro(module, KEY_ARCHIVE);
  PyModule_AddIntMacro(module, KEY_PROGRAM);
  PyModule_AddIntMacro(module, KEY_CHANNEL);
  PyModule_AddIntMacro(module, KEY_FAVORITES);
  PyModule_AddIntMacro(module, KEY_EPG);
  PyModule_AddIntMacro(module, KEY_PVR);
  PyModule_AddIntMacro(module, KEY_MHP);
  PyModule_AddIntMacro(module, KEY_LANGUAGE);
  PyModule_AddIntMacro(module, KEY_TITLE);
  PyModule_AddIntMacro(module, KEY_SUBTITLE);
  PyModule_AddIntMacro(module, KEY_ANGLE);
  PyModule_AddIntMacro(module, KEY_ZOOM);
  PyModule_AddIntMacro(module, KEY_MODE);
  PyModule_AddIntMacro(module, KEY_KEYBOARD);
  PyModule_AddIntMacro(module, KEY_SCREEN);
  PyModule_AddIntMacro(module, KEY_PC);
  PyModule_AddIntMacro(module, KEY_TV);
  PyModule_AddIntMacro(module, KEY_TV2);
  PyModule_AddIntMacro(module, KEY_VCR);
  PyModule_AddIntMacro(module, KEY_VCR2);
  PyModule_AddIntMacro(module, KEY_SAT);
  PyModule_AddIntMacro(module, KEY_SAT2);
  PyModule_AddIntMacro(module, KEY_CD);
  PyModule_AddIntMacro(module, KEY_TAPE);
  PyModule_AddIntMacro(module, KEY_RADIO);
  PyModule_AddIntMacro(module, KEY_TUNER);
  PyModule_AddIntMacro(module, KEY_PLAYER);
  PyModule_AddIntMacro(module, KEY_TEXT);
  PyModule_AddIntMacro(module, KEY_DVD);
  PyModule_AddIntMacro(module, KEY_AUX);
  PyModule_AddIntMacro(module, KEY_MP3);
  PyModule_AddIntMacro(module, KEY_AUDIO);
  PyModule_AddIntMacro(module, KEY_VIDEO);
  PyModule_AddIntMacro(module, KEY_DIRECTORY);
  PyModule_AddIntMacro(module, KEY_LIST);
  PyModule_AddIntMacro(module, KEY_MEMO);
  PyModule_AddIntMacro(module, KEY_CALENDAR);
  PyModule_AddIntMacro(module, KEY_RED);
  PyModule_AddIntMacro(module, KEY_GREEN);
  PyModule_AddIntMacro(module, KEY_YELLOW);
  PyModule_AddIntMacro(module, KEY_BLUE);
  PyModule_AddIntMacro(module, KEY_CHANNELUP);
  PyModule_AddIntMacro(module, KEY_CHANNELDOWN);
  PyModule_AddIntMacro(module, KEY_FIRST);
  PyModule_AddIntMacro(module, KEY_LAST);
  PyModule_AddIntMacro(module, KEY_AB);
  PyModule_AddIntMacro(module, KEY_NEXT);
  PyModule_AddIntMacro(module, KEY_RESTART);
  PyModule_AddIntMacro(module, KEY_SLOW);
  PyModule_AddIntMacro(module, KEY_SHUFFLE);
  PyModule_AddIntMacro(module, KEY_BREAK);
  PyModule_AddIntMacro(module, KEY_PREVIOUS);
  PyModule_AddIntMacro(module, KEY_DIGITS);
  PyModule_AddIntMacro(module, KEY_TEEN);
  PyModule_AddIntMacro(module, KEY_TWEN);
  PyModule_AddIntMacro(module, KEY_VIDEOPHONE);
  PyModule_AddIntMacro(module, KEY_GAMES);
  PyModule_AddIntMacro(module, KEY_ZOOMIN);
  PyModule_AddIntMacro(module, KEY_ZOOMOUT);
  PyModule_AddIntMacro(module, KEY_ZOOMRESET);
  PyModule_AddIntMacro(module, KEY_WORDPROCESSOR);
  PyModule_AddIntMacro(module, KEY_EDITOR);
  PyModule_AddIntMacro(module, KEY_SPREADSHEET);
  PyModule_AddIntMacro(module, KEY_GRAPHICSEDITOR);
  PyModule_AddIntMacro(module, KEY_PRESENTATION);
  PyModule_AddIntMacro(module, KEY_DATABASE);
  PyModule_AddIntMacro(module, KEY_NEWS);
  PyModule_AddIntMacro(module, KEY_VOICEMAIL);
  PyModule_AddIntMacro(module, KEY_ADDRESSBOOK);
  PyModule_AddIntMacro(module, KEY_MESSENGER);
  PyModule_AddIntMacro(module, KEY_DISPLAYTOGGLE);
  PyModule_AddIntMacro(module, KEY_SPELLCHECK);
  PyModule_AddIntMacro(module, KEY_LOGOFF);
  PyModule_AddIntMacro(module, KEY_DOLLAR);
  PyModule_AddIntMacro(module, KEY_EURO);
  PyModule_AddIntMacro(module, KEY_FRAMEBACK);
  PyModule_AddIntMacro(module, KEY_FRAMEFORWARD);
  PyModule_AddIntMacro(module, KEY_CONTEXT_MENU);
  PyModule_AddIntMacro(module, KEY_MEDIA_REPEAT);
  PyModule_AddIntMacro(module, KEY_DEL_EOL);
  PyModule_AddIntMacro(module, KEY_DEL_EOS);
  PyModule_AddIntMacro(module, KEY_INS_LINE);
  PyModule_AddIntMacro(module, KEY_DEL_LINE);
  PyModule_AddIntMacro(module, KEY_FN);
  PyModule_AddIntMacro(module, KEY_FN_ESC);
  PyModule_AddIntMacro(module, KEY_FN_F1);
  PyModule_AddIntMacro(module, KEY_FN_F2);
  PyModule_AddIntMacro(module, KEY_FN_F3);
  PyModule_AddIntMacro(module, KEY_FN_F4);
  PyModule_AddIntMacro(module, KEY_FN_F5);
  PyModule_AddIntMacro(module, KEY_FN_F6);
  PyModule_AddIntMacro(module, KEY_FN_F7);
  PyModule_AddIntMacro(module, KEY_FN_F8);
  PyModule_AddIntMacro(module, KEY_FN_F9);
  PyModule_AddIntMacro(module, KEY_FN_F10);
  PyModule_AddIntMacro(module, KEY_FN_F11);
  PyModule_AddIntMacro(module, KEY_FN_F12);
  PyModule_AddIntMacro(module, KEY_FN_1);
  PyModule_AddIntMacro(module, KEY_FN_2);
  PyModule_AddIntMacro(module, KEY_FN_D);
  PyModule_AddIntMacro(module, KEY_FN_E);
  PyModule_AddIntMacro(module, KEY_FN_F);
  PyModule_AddIntMacro(module, KEY_FN_S);
  PyModule_AddIntMacro(module, KEY_FN_B);
  PyModule_AddIntMacro(module, KEY_BRL_DOT1);
  PyModule_AddIntMacro(module, KEY_BRL_DOT2);
  PyModule_AddIntMacro(module, KEY_BRL_DOT3);
  PyModule_AddIntMacro(module, KEY_BRL_DOT4);
  PyModule_AddIntMacro(module, KEY_BRL_DOT5);
  PyModule_AddIntMacro(module, KEY_BRL_DOT6);
  PyModule_AddIntMacro(module, KEY_BRL_DOT7);
  PyModule_AddIntMacro(module, KEY_BRL_DOT8);
  PyModule_AddIntMacro(module, KEY_BRL_DOT9);
  PyModule_AddIntMacro(module, KEY_BRL_DOT10);
  PyModule_AddIntMacro(module, KEY_NUMERIC_0);
  PyModule_AddIntMacro(module, KEY_NUMERIC_1);
  PyModule_AddIntMacro(module, KEY_NUMERIC_2);
  PyModule_AddIntMacro(module, KEY_NUMERIC_3);
  PyModule_AddIntMacro(module, KEY_NUMERIC_4);
  PyModule_AddIntMacro(module, KEY_NUMERIC_5);
  PyModule_AddIntMacro(module, KEY_NUMERIC_6);
  PyModule_AddIntMacro(module, KEY_NUMERIC_7);
  PyModule_AddIntMacro(module, KEY_NUMERIC_8);
  PyModule_AddIntMacro(module, KEY_NUMERIC_9);
  PyModule_AddIntMacro(module, KEY_NUMERIC_STAR);
  PyModule_AddIntMacro(module, KEY_NUMERIC_POUND);
}