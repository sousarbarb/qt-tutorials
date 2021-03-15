#include "renderwindow.h"

RenderWindow::RenderWindow() {
  // Tell the render window to use the OpenGL surface type
  setSurfaceType(QWindow::OpenGLSurface);

  // Enable core profile (rather than compatibility profile) that runs version 3.2
  QSurfaceFormat format;
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setVersion(3, 2);
  setFormat(format);

  // Create an OpenGL context
  openGLContext = new QOpenGLContext();
  openGLContext->setFormat(format);
  openGLContext->create();
  openGLContext->makeCurrent(this);
}

void RenderWindow::initializeGL() {
  // This function is called before the rendering starts
  openGLFunctions = openGLContext->functions();

  // Vertex shader
  static const char *vertexShaderSource =
      "#version 330 core\n"
      "layout(location = 0) in vec2 posAttr;\n"
      "void main() {\n"
      "gl_Position = vec4(posAttr, 0.0, 1.0); }";

  // Fragment shader
  static const char *fragmentShaderSource =
      "#version 330 core\n"
      "out vec4 col;\n"
      "void main() {\n"
      "col = vec4(1.0, 0.0, 0.0, 1.0); }";

  shaderProgram = new QOpenGLShaderProgram(this);
  shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex  , vertexShaderSource);
  shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  shaderProgram->link();

  // Declare a vertice array
  GLfloat vertices[] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
     0.0f,  1.0f
  };

  vao = new QOpenGLVertexArrayObject();
  vao->create();
  vao->bind();

  // Defining vbo_vertices
  vbo_vertices = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo_vertices->create();
  vbo_vertices->setUsagePattern(QOpenGLBuffer::StaticDraw);
  vbo_vertices->bind();
  vbo_vertices->allocate(vertices,sizeof(vertices)*sizeof(GLfloat));

  vao->release();
}

void RenderWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  glViewport(0,0,width(),height());
  glClearColor(0.39f,0.58f,0.93f,1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  vao->bind();
  shaderProgram->bind();
  shaderProgram->bindAttributeLocation("posAttr",0);
  shaderProgram->enableAttributeArray(0);
  shaderProgram->setAttributeBuffer(0,GL_FLOAT,0,2);
  glDrawArrays(GL_TRIANGLES,0,3);
  shaderProgram->release();
  vao->release();
}

void RenderWindow::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event);
  glViewport(0,0,this->width(),this->height());
  this->update();
}
