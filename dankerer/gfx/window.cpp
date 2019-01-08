//
// Created by dan on 31/10/18.
//

#include "window.h"
#include "renderPass.h"

using namespace dk::gfx;

Window::Window(GLFWwindow* window, int width, int height, std::string const& cfgFilePath)
    : m_window(window)
    , m_width(width)
    , m_height(height)
    , m_device(new Device(width, height))
    , m_camera(m_width, m_height)
    , m_forwardRenderer(Renderer::RendererType::Forward, m_device.get())
    , m_deferredRenderer(Renderer::RendererType::Deferred, m_device.get())
{
    //set the config file manually for now
    m_configFile.m_rendType = Renderer::RendererType::Deferred;
    m_configFile.m_vsync = true;
}

void Window::setTitle(std::string const &title) {
    glfwSetWindowTitle(m_window, title.c_str());
}

void Window::handleKeyboard(GLFWwindow* window, int key, int scanCode, int actions, int mods) {
    if (key == GLFW_KEY_W && actions == GLFW_REPEAT) {
        m_camera.forward();

    } else if (key == GLFW_KEY_S && actions == GLFW_REPEAT) {
        m_camera.backward();

    } else if (key == GLFW_KEY_A && actions == GLFW_REPEAT) {
        m_camera.left();

    } else if (key == GLFW_KEY_D && actions == GLFW_REPEAT) {
        m_camera.right();
    } else if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS) {
        exit(0);
    }
}

void Window::handleMouse(GLFWwindow* window, double xpos, double ypos) {
    m_camera.mouse(xpos, ypos);
}

void Window::init() {
	m_sceneLoader.getScene()->getMesh()->loadFromFile("C:/Users/dan/dev/dkr/dankerer/resources/chalet.obj", *(m_device.get()));

	auto gvert = m_device->createShader(GL_VERTEX_SHADER);
	auto& gvshader = m_device->accessShader(gvert);
	gvshader.compile("C:/Users/dan/dev/dkr/dankerer/resources/gbuffer.vert");

	auto gfrag = m_device->createShader(GL_FRAGMENT_SHADER);
	auto& gfshader = m_device->accessShader(gfrag);
	gfshader.compile("C:/Users/dan/dev/dkr/dankerer/resources/gbuffer.frag");

	auto gprog = m_device->createShaderProgram();
	auto gfvprog = m_device->accessShaderProgram(gprog);
	gfvprog.addShader(gvert, m_device.get());
	gfvprog.addShader(gfrag, m_device.get());

	m_ubo = m_device->createUniformBuffer();
    CameraMatrix cameraMatrix{};
    cameraMatrix.proj = m_camera.getProj();
    cameraMatrix.view = m_camera.getView();

    if (m_configFile.m_rendType == Renderer::RendererType::Forward) {
        //configure
    } else if (m_configFile.m_rendType == Renderer::RendererType::Deferred) {
        //add the passes...
		m_gbuf = new RenderPass(m_device.get());
		m_gbuf->setName("gpass");
		m_gbuf->setClearColour(glm::vec4(0.0f, 0.0f, 0.1f, 0.0f));

		m_gbuf->addOutput("position");
		m_gbuf->addOutput("normals");
		m_gbuf->addOutput("albedo");
		m_gbuf->addOutput("specular");

		//RenderPass* lighting = new RenderPass(m_device.get());
		//lighting->setName("lighting");

  //      lighting->addInput("position");
  //      lighting->addInput("normals");
  //      lighting->addInput("albedo");
  //      lighting->addInput("specular");

		m_deferredRenderer.addRenderPass(m_gbuf);
		//m_deferredRenderer.addRenderPass(lighting);

		CommandBuffer* cmd = m_deferredRenderer.getCommandBuffer();
		cmd->beginRenderPass(m_gbuf);
		m_sceneLoader.getScene()->getMesh()->addToBuffer(cmd, m_device.get());
		cmd->setShaderProgram(&gfvprog);

		auto& ubuf = m_device->accessUniformBuffer(m_ubo);
		ubuf.bind((void*)&cameraMatrix, sizeof(cameraMatrix));
		ubuf.connectToShader(3);

		cmd->execute();
		
		cmd->endRenderPass();
		cmd->flush();
    }
}

void Window::update(float deltaTime) {
    CameraMatrix cameraMatrix{};
    cameraMatrix.proj = m_camera.getProj();
    cameraMatrix.view = m_camera.getView();
    m_device->accessUniformBuffer(m_ubo).bind((void*)&cameraMatrix, sizeof(cameraMatrix));

	CommandBuffer* cmd = m_deferredRenderer.getCommandBuffer();
	cmd->beginRenderPass(m_gbuf);
	m_sceneLoader.getScene()->getMesh()->addToBuffer(cmd, m_device.get());
	//cmd->setShaderProgram(&gfvprog);

	auto& ubuf = m_device->accessUniformBuffer(m_ubo);
	ubuf.bind((void*)&cameraMatrix, sizeof(cameraMatrix));
	ubuf.connectToShader(3);

	cmd->execute();

	cmd->endRenderPass();
	cmd->flush();

}