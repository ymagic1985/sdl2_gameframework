
#include "sandbox3D.h"

Sandbox3D::Sandbox3D() : Man520::Layer("Sandbox3D"), cubePositions{
  glm::vec3( 0.0f,  0.0f,  0.0f),
  glm::vec3( 2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f,  2.0f, -2.5f),
  glm::vec3( 1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
 } {
}

Sandbox3D::~Sandbox3D() {
    
}

void Sandbox3D::onAttach() {
    boxShader = Man520::Shader::create("boxShader", "assets/shaders/test.vs", "assets/shaders/test.fs");
    lightCubeShader = Man520::Shader::create("lightShader", "assets/shaders/lightcube.vs", "assets/shaders/lightcube.fs");
    lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
         //position            //textcoords //normal
         //front
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f,  0.0f,  -1.0f,  // top right
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,  0.0f,  -1.0f,  // top left
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  0.0f,  -1.0f,  // bottom left
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  0.0f,  -1.0f,  // bottom right
         //back
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  0.0f, 1.0f,  // top right
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  0.0f, 1.0f,  // top left
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f,  0.0f, 1.0f,  // bottom left
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f,  0.0f, 1.0f,  // bottom right
         //top
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f, -1.0f,  0.0f,  // top right
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f, -1.0f,  0.0f,  // top left
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   0.0f, -1.0f,  0.0f,  // bottom left
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f, -1.0f,  0.0f,  // bottom right
        //bottm
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  1.0f,  0.0f,  // top right
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  1.0f,  0.0f,  // top left
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  1.0f,  0.0f,  // bottom left
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  1.0f,  0.0f,  // bottom right
        //left
        -0.5f,  0.5f,  0.5f,   1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,  // top right
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,  // top left
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,  // bottom left
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,  // bottom right
        //right
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   1.0f,  0.0f,  0.0f,  // top right
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   1.0f,  0.0f,  0.0f,  // top left
         0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   1.0f,  0.0f,  0.0f,  // bottom left
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   1.0f,  0.0f,  0.0f,  // bottom right
   };
    boxVA = Man520::VertexArray::create();
    boxVB = Man520::VertexBuffer::create(vertices, sizeof(vertices));
    Man520::BufferLayout boxBufferLayout({
        {Man520::ShaderDataType::Float3, "position"},
        {Man520::ShaderDataType::Float2, "texcoord"},
        {Man520::ShaderDataType::Float3, "normal"}
    });
    boxVB->setLayout(boxBufferLayout);
    boxVA->addVertexBuffer(boxVB);
    unsigned int indices[] = {  // note that we start from 0!
         0, 1, 2,  // first Triangle
         0, 2, 3,   // second Triangle

         4, 5, 6,
         4, 6, 7,

         8, 9, 10,
         8, 10, 11,

         12, 13, 14,
         12, 14, 15,

         16, 17, 18,
         16, 18, 19,

         20, 21, 22,
         20, 22, 23
    };
    boxIB = Man520::IndexBuffer::create(indices, sizeof(indices)/sizeof(uint32_t));
    boxVA->setIndexBuffer(boxIB);

    //-----------------------------
    lightVA = Man520::VertexArray::create();
    lightVA->addVertexBuffer(boxVB);
    lightVA->setIndexBuffer(boxIB);
    //------------------------------

    texture1 = Man520::Texture2D::create("images/container.jpeg");
    texture2 = Man520::Texture2D::create("images/awesomeface.png");
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    boxShader->bind();
    boxShader->setInt("texture1", 0);
    boxShader->setInt("texture2", 1);
}

void Sandbox3D::onDetach() {

}

void Sandbox3D::onUpdate() {
  //deltatime = app->getDeltaTime();

  boxShader->bind();

  glm::mat4 projection = glm::mat4(1.0f);
  projection = glm::perspective(glm::radians(fov), (float)800/(float)600, 0.1f, 100.0f);

  glm::mat4 vp = projection * camera.getViewMat4();
  boxShader->setMat4("vp", vp);
  boxShader->setVec3("lightColor",  1.0f, 1.0f, 1.0f);
  boxShader->setVec3("lightPos", lightPos);
  boxShader->setVec3("viewPos", camera.getPosition());

  boxVA->bind();
  for(int i = 0; i < 10; i++) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, cubePositions[i]);
      float angle = 20*i;
      if(i%3 == 0)
          angle = (float)SDL_GetTicks() / 1000.0f * 25.0f;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      boxShader->setMat4("model", model);
      texture1->bind(0);
      texture2->bind(1);
      Man520::RenderCommand::drawIndexed(boxVA);
  }

  lightCubeShader->bind();
  lightCubeShader->setMat4("projection", projection);
  lightCubeShader->setMat4("view", camera.getViewMat4());
  glm::mat4 model = glm::mat4(1.0f);
  lightPos.x = 1.0f + sin((float)SDL_GetTicks()/1000.0f)*2.0f;
  lightPos.y = sin((float)SDL_GetTicks()/1000.0f/2.0f)*1.0f;
  model = glm::translate(model, lightPos);
  model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
  lightCubeShader->setMat4("model", model);
  Man520::RenderCommand::drawIndexed(lightVA);

  //if(printFPS) std::cout<<"FPS: "<<1/(float)app->getDeltaTime()*1000.0f<<"\n";
}

bool Sandbox3D::onEvent(SDL_Event& event) {
  if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_f) {
      printFPS = !printFPS;
      return true;
  }else if(event.type == SDL_MOUSEWHEEL) {
      fov -= (float)event.wheel.y;
      if(fov > 45.0f) fov = 45.0f;
      if(fov < 1.0f) fov = 1.0f;
      wheelY = (float)event.wheel.y;
      return true;
  }else if(event.type == SDL_MOUSEMOTION){
      int x, y;
      SDL_GetMouseState(&x,&y);
      
      if(firstmouse) {
          mouseX = (float)x;
          mouseY = (float)y;
          firstmouse = false;
      }

      float sensitivity = 0.3f;

      float offsetX = sensitivity* ((float)x - mouseX);
      float offsetY = sensitivity* ((float)y - mouseY);

      mouseX = (float)x;
      mouseY = (float)y;
          
      camera.lookAround(offsetX, offsetY);
      return true;
  }
  return false;
}


