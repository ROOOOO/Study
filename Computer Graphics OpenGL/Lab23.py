import glfw
from OpenGL.GL import *
import math
from myCGClasses import *


angles = [0, 0, 0]
scale = 0.5
carcass = False
parts = 3
vp_size = 640
sphere = Sphere(0, 0, 0, 0.5)


def main():
    global angles, angley, anglez, scale, carcass, sphere
    if not glfw.init():
        return
    window = glfw.create_window(640, 640, "Lab2", None, None)
    if not window:
        glfw.terminate()
        return
    glfw.make_context_current(window)
    glfw.set_key_callback(window, key_callback)
    glfw.set_framebuffer_size_callback(window, resize_callback)
    glfw.set_window_pos_callback(window, drag_callback)
    l_cube = Cube(0, 0, 0, 1)
    # r_cube = Cube(0, 0, 0, 1)
    sphere.recount(parts)
    while not glfw.window_should_close(window):
        glEnable(GL_DEPTH_TEST)
        glDepthFunc(GL_LESS)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        set_projection()
        glLoadIdentity()
        sphere.draw(scale, angles, [0.3, 0.0, 0.4], carcass)
        # r_cube.draw(scale, angles, [0.3, 0.2, 0.4], carcass)
        l_cube.draw(0.5, [0, 0, 0], [-0.5, 0.0, -0.25], False)
        glfw.swap_buffers(window)
        glfw.poll_events()
    glfw.destroy_window(window)
    glfw.terminate()


def set_projection():
    glMatrixMode(GL_PROJECTION)
    cosf = math.cos(0.7853)
    cost = math.cos(0.6108)
    sinf = math.sin(0.7853)
    sint = math.sin(0.6108)
    sq3 = math.sqrt(3)
    sq2 = math.sqrt(2)
    sq6 = math.sqrt(6)
    glLoadIdentity()
    glMultMatrixf([cosf, sinf*sint, sinf*cost, 0,
                   0, cost, -sint, 0,
                   sinf, -cosf*sint, -cosf*cost, 0,
                   0, 0, 0, 1])
    # glMultMatrixf([1, 0, 0, 0,
    #                0, 1, 0, 0,
    #                0, 0, -1, 0,
    #                0, 0, 0, 1])
    # glMultMatrixf([1, 0, 0, 0,
    #                0, cost, sint, 0,
    #                0, -sint, cost, 0,
    #                0, 0, 0, 1])
    # glMultMatrixf([cosf, 0, -sinf, 0,
    #                0, 1, 0, 0,
    #                sinf, 0, cosf, 0,
    #                0, 0, 0, 1])
    glMatrixMode(GL_MODELVIEW)


def resize_callback(window, width, height):
    global vp_size
    vp_size = width if width < height else height
    glViewport(0, 0, vp_size, vp_size)


def drag_callback(window, xpos, ypos):
    glViewport(0, 0, vp_size, vp_size)


def key_callback(window, key, scancode, action, mods):
    global angles, scale, carcass, parts, sphere
    if key == glfw.KEY_UP:
        angles[0] = angles[0] % 360
        angles[0] += 5


    if key == glfw.KEY_DOWN:
        angles[0] = angles[0] % 360
        angles[0] -= 5


    if key == glfw.KEY_RIGHT:
        angles[2] = angles[2] % 360
        angles[2] -= 5

    if key == glfw.KEY_LEFT:
        angles[2] = angles[2] % 360
        angles[2] += 5

    if key == glfw.KEY_X:
        angles[1] = angles[1] % 360
        angles[1] -= 5

    if key == glfw.KEY_Z:
        angles[1] = angles[1] % 360
        angles[1] += 5

    if key == glfw.KEY_A:
        scale -= 0.03 if scale > 0.1 else 0

    if key == glfw.KEY_S:
        scale += 0.03 if scale < 10 else 0

    if action==glfw.PRESS:
        if key == glfw.KEY_Q:
            if carcass:
                carcass = False
            else:
                carcass = True

        if key == glfw.KEY_M:
            parts += 1 if parts < 5 else 0
            sphere.recount(parts)

        if key == glfw.KEY_L:
            parts -= 1 if parts > 0 else 0
            sphere.recount(parts)

main()
