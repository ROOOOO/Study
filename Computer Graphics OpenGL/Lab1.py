import glfw
import OpenGL
from OpenGL.GL import *

delta = 0.1
angle = 0.0

def main():
    global delta
    global angle
    # Initialize the library
    if not glfw.init():
        return
    # Create a windowed mode window and its OpenGL context
    window = glfw.create_window(640, 640, "Lab1", None, None)
    if not window:
        glfw.terminate()
        return
    # Make the window's context current
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    # Loop until the user closes the window
    while not glfw.window_should_close(window):
        # Render here, e.g. using pyOpenGL

        glClear(GL_COLOR_BUFFER_BIT)
        glLoadIdentity()
        glClearColor(1.0, 1.0, 1.0, 1.0)
        glPushMatrix()

        glRotatef(angle, 0, 0, 1)

        glBegin(GL_QUADS)

        glColor3f(0.0,0.0,0.0)
        glVertex3f( 0.5, 0.5, 0.0)
        glColor3f(1.0,0.0,0.0)
        glVertex3f(-0.5, 0.5, 0.0)
        glColor3f(0.0,0.0,1.0)
        glVertex3f(-0.5, -0.5, 0.0)
        glColor3f(1.0,0.0,1.0)
        glVertex3f( 0.5, -0.5, 0.0)


        glEnd()

        glPopMatrix()
        angle += delta

        # Swap front and back buffers
        glfw.swap_buffers(window)
        # Poll for and process events
        glfw.poll_events()
    glfw.destroy_window(window)
    glfw.terminate()


def key_callback(window, key, scancode, action, mods):
    global delta
    global angle
    if action == glfw.PRESS:
        if key == 262:
            delta = -0.1
            angle = angle%360
        if key == 263:
            delta = 0.1
            angle = angle%360

main()