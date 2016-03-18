import glfw
from OpenGL.GL import *
import math


class Cube(object):
    def __init__(self, center_x, center_y, center_z, edge_len):
        e = edge_len/2
        self.front_quad = [[center_x+e, center_y+e, center_z+e],
                           [center_x+e, center_y-e, center_z+e],
                           [center_x-e, center_y-e, center_z+e],
                           [center_x-e, center_y+e, center_z+e]]
        self.back_quad = [[center_x+e, center_y+e, center_z-e],
                           [center_x+e, center_y-e, center_z-e],
                           [center_x-e, center_y-e, center_z-e],
                           [center_x-e, center_y+e, center_z-e]]
        self.left_quad = [[center_x-e, center_y+e, center_z+e],
                          [center_x-e, center_y-e, center_z+e],
                          [center_x-e, center_y-e, center_z-e],
                          [center_x-e, center_y+e, center_z-e]]
        self.right_quad = [[center_x+e, center_y+e, center_z+e],
                          [center_x+e, center_y-e, center_z+e],
                          [center_x+e, center_y-e, center_z-e],
                          [center_x+e, center_y+e, center_z-e]]
        self.top_quad = [[center_x+e, center_y+e, center_z+e],
                         [center_x-e, center_y+e, center_z+e],
                         [center_x-e, center_y+e, center_z-e],
                         [center_x+e, center_y+e, center_z-e]]
        self.bottom_quad = [[center_x+e, center_y-e, center_z+e],
                            [center_x-e, center_y-e, center_z+e],
                            [center_x-e, center_y-e, center_z-e],
                            [center_x+e, center_y-e, center_z-e]]

    def draw(self, scale, angles, translates, carcass):
        glLoadIdentity()
        glPushMatrix()
        glTranslatef(translates[0], translates[1], translates[2])
        glScalef(scale, scale, scale)
        glRotatef(angles[0], 1, 0, 0)
        glRotatef(angles[1], 0, 1, 0)
        glRotatef(angles[2], 0, 0, 1)
        if carcass:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
        else:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
        glBegin(GL_QUADS)
        glColor4f(0, 0, 1, 1)
        glVertex3f(self.front_quad[0][0], self.front_quad[0][1], self.front_quad[0][2])
        glVertex3f(self.front_quad[1][0], self.front_quad[1][1], self.front_quad[1][2])
        glVertex3f(self.front_quad[2][0], self.front_quad[2][1], self.front_quad[2][2])
        glVertex3f(self.front_quad[3][0], self.front_quad[3][1], self.front_quad[3][2])
        glColor4f(0, 1, 1, 1)
        glVertex3f(self.right_quad[0][0], self.right_quad[0][1], self.right_quad[0][2])
        glVertex3f(self.right_quad[1][0], self.right_quad[1][1], self.right_quad[1][2])
        glVertex3f(self.right_quad[2][0], self.right_quad[2][1], self.right_quad[2][2])
        glVertex3f(self.right_quad[3][0], self.right_quad[3][1], self.right_quad[3][2])
        glColor4f(1, 1, 1, 1)
        glVertex3f(self.left_quad[0][0], self.left_quad[0][1], self.left_quad[0][2])
        glVertex3f(self.left_quad[1][0], self.left_quad[1][1], self.left_quad[1][2])
        glVertex3f(self.left_quad[2][0], self.left_quad[2][1], self.left_quad[2][2])
        glVertex3f(self.left_quad[3][0], self.left_quad[3][1], self.left_quad[3][2])
        glColor4f(1, 1, 0, 1)
        glVertex3f(self.top_quad[0][0], self.top_quad[0][1], self.top_quad[0][2])
        glVertex3f(self.top_quad[1][0], self.top_quad[1][1], self.top_quad[1][2])
        glVertex3f(self.top_quad[2][0], self.top_quad[2][1], self.top_quad[2][2])
        glVertex3f(self.top_quad[3][0], self.top_quad[3][1], self.top_quad[3][2])
        glColor4f(1, 0, 0, 1)
        glVertex3f(self.bottom_quad[0][0], self.bottom_quad[0][1], self.bottom_quad[0][2])
        glVertex3f(self.bottom_quad[1][0], self.bottom_quad[1][1], self.bottom_quad[1][2])
        glVertex3f(self.bottom_quad[2][0], self.bottom_quad[2][1], self.bottom_quad[2][2])
        glVertex3f(self.bottom_quad[3][0], self.bottom_quad[3][1], self.bottom_quad[3][2])
        glColor4f(1, 0, 1, 1)
        glVertex3f(self.back_quad[0][0], self.back_quad[0][1], self.back_quad[0][2])
        glVertex3f(self.back_quad[1][0], self.back_quad[1][1], self.back_quad[1][2])
        glVertex3f(self.back_quad[2][0], self.back_quad[2][1], self.back_quad[2][2])
        glVertex3f(self.back_quad[3][0], self.back_quad[3][1], self.back_quad[3][2])
        glEnd()
        glPopMatrix()


class Sphere(object):
    def __init__(self, center_x, center_y, center_z, radius):
        self.triangles = [[[center_x, center_y+radius, center_z], [center_x+radius, center_y, center_z], [center_x, center_y, center_z+radius]],
                          [[center_x-radius, center_y, center_z], [center_x, center_y+radius, center_z], [center_x, center_y, center_z+radius]],
                          [[center_x-radius, center_y, center_z], [center_x, center_y-radius, center_z], [center_x, center_y, center_z+radius]],
                          [[center_x+radius, center_y, center_z], [center_x, center_y-radius, center_z], [center_x, center_y, center_z+radius]],
                          [[center_x, center_y+radius, center_z], [center_x+radius, center_y, center_z], [center_x, center_y, center_z-radius]],
                          [[center_x-radius, center_y, center_z], [center_x, center_y+radius, center_z], [center_x, center_y, center_z-radius]],
                          [[center_x-radius, center_y, center_z], [center_x, center_y-radius, center_z], [center_x, center_y, center_z-radius]],
                          [[center_x+radius, center_y, center_z], [center_x, center_y-radius, center_z], [center_x, center_y, center_z-radius]]]
        self.to_draw = []
        self.radius = radius
        self.colors = []

    def draw(self, scale, angles, translates, carcass):
        glPushMatrix()
        glTranslatef(translates[0], translates[1], translates[2])
        glScalef(scale, scale, scale)
        glRotatef(angles[0], 1, 0, 0)
        glRotatef(angles[1], 0, 1, 0)
        glRotatef(angles[2], 0, 0, 1)
        if carcass:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
        else:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
        glEnableClientState(GL_VERTEX_ARRAY)
        glEnableClientState(GL_COLOR_ARRAY)
        glVertexPointer(3, GL_FLOAT, 0, self.to_draw)
        glColorPointer(3, GL_FLOAT, 0, self.colors)
        glDrawArrays(GL_TRIANGLES, 0, int(len(self.to_draw)/3))
        glDisableClientState(GL_VERTEX_ARRAY)
        glDisableClientState(GL_COLOR_ARRAY)
        glPopMatrix()
        return

    def recount_and_draw(self, scale, angles, translates, carcass, times):
        self.recount(times)
        self.draw(scale, angles, translates, carcass)

    def recount(self, times):
        self.to_draw = []
        i = 0
        while i < 8:
            self.count(self.triangles[i], times)
            i += 1
        i = 0

    def count(self, v, times):
        if times==0:
            r = self.radius
            i = 0
            while i < 3:
                x = v[i][0]
                y = v[i][1]
                z = v[i][2]
                v[i][0] = x/(math.sqrt(x*x+y*y+z*z))*r
                v[i][1] = y/(math.sqrt(x*x+y*y+z*z))*r
                v[i][2] = z/(math.sqrt(x*x+y*y+z*z))*r
                i += 1
            self.colors.extend([1, 0, 0, 1, 0, 1, 0, 1, 0])
            self.to_draw.extend([v[0][0], v[0][1], v[0][2], v[1][0], v[1][1], v[1][2], v[2][0], v[2][1], v[2][2]])
        else:
            self.count([[v[0][0], v[0][1], v[0][2]],
                                [(v[1][0]+v[0][0])/2, (v[1][1]+v[0][1])/2, (v[1][2]+v[0][2])/2],
                                [(v[2][0]+v[0][0])/2, (v[2][1]+v[0][1])/2, (v[2][2]+v[0][2])/2]], times-1)
            self.count([[(v[1][0]+v[0][0])/2, (v[1][1]+v[0][1])/2, (v[1][2]+v[0][2])/2],
                                [v[1][0], v[1][1], v[1][2]],
                                [(v[2][0]+v[1][0])/2, (v[2][1]+v[1][1])/2, (v[2][2]+v[1][2])/2]], times-1)
            self.count([[(v[2][0]+v[0][0])/2, (v[2][1]+v[0][1])/2, (v[2][2]+v[0][2])/2],
                                [(v[2][0]+v[1][0])/2, (v[2][1]+v[1][1])/2, (v[2][2]+v[1][2])/2],
                                [v[2][0], v[2][1], v[2][2]]], times-1)
            self.count([[(v[1][0]+v[0][0])/2, (v[1][1]+v[0][1])/2, (v[1][2]+v[0][2])/2],
                                [(v[2][0]+v[1][0])/2, (v[2][1]+v[1][1])/2, (v[2][2]+v[1][2])/2],
                                [(v[2][0]+v[0][0])/2, (v[2][1]+v[0][1])/2, (v[2][2]+v[0][2])/2]], times-1)
