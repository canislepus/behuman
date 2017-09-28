#ifndef MODEL_H
#define MODEL_H

#include <GL/gl.h>


class Model
{

    public:
        Model();
        virtual ~Model();

        //Vertex Buffer Object
        GLuint vbo;
        //Index Buffer Object
        GLuint ibo;
        //UV Buffer Object (Texture coordinates);
        GLuint uvbo;
    protected:
    private:
};

#endif // MODEL_H
