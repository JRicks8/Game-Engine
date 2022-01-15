#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	Mesh::name = "noName";

	SetupBuffers();
}

void Mesh::Draw(Shader& shader, glm::vec3 t, glm::vec3 s)
{
	shader.Use();
	// determine # of diffuse and specular textures and send info to the shader
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i].Bind();

		std::string number;
		std::string type = textures[i].type;
		if (type == "diffuse")
			number = std::to_string(diffuseNr++);
		else if (type == "specular")
			number = std::to_string(specularNr++);

		shader.SetFloat(("material.texture_" + type + number).c_str(), i);
		textures[i].Bind();
	}

	// set material properties
	shader.SetFloat("material.shininess", shininess);

	// set model matrix
	glm::mat4 drawMat = glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0f), scale);
	drawMat = glm::translate(drawMat, t);
	drawMat = glm::scale(drawMat, s);
	
	shader.SetMat4("model", drawMat);

	glActiveTexture(GL_TEXTURE0);

	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // unbind vao
}

void Mesh::GeneratePhysBody(float mass)
{
	hasPhysicsBody = true;
	physBody.GenerateShape(vertices, indices, scale.x);
	physBody.GenerateBodyWithMass(mass, btVector3(position.x, position.y, position.z), btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w), this);
}

void Mesh::SyncRigidBody()
{
	position = glm::vec3(physBody.body->getWorldTransform().getOrigin().x(),
						 physBody.body->getWorldTransform().getOrigin().y(),
						 physBody.body->getWorldTransform().getOrigin().z());
	rotation = glm::quat(physBody.body->getWorldTransform().getRotation().x(),
						 physBody.body->getWorldTransform().getRotation().y(),
						 physBody.body->getWorldTransform().getRotation().z(),
						 physBody.body->getWorldTransform().getRotation().w());
}

void Mesh::SetPosition(glm::vec3 p)
{
	position = p;
}

void Mesh::SetRotation(glm::quat r)
{
	rotation = r;
}

void Mesh::SetScale(glm::vec3 s)
{
	scale = s;
}

glm::vec3 Mesh::GetRotationEuler(bool radians)
{
	if (radians)
		return glm::vec3(glm::eulerAngles(rotation));

	glm::vec3 rot = glm::eulerAngles(rotation);
	return glm::vec3(glm::degrees(rot.x), glm::degrees(rot.y), glm::degrees(rot.z));
}

void Mesh::PrintInfo()
{
	std::cout << "---Mesh Information---\n";
	std::cout << "name: " << name << '\n';
	std::cout << "position: " << position.x << " / " << position.y << " / " << position.z << '\n';
	std::cout << "qRot: " << GetRotation().x << " / " << GetRotation().y << " / " << GetRotation().z << " / " << GetRotation().w << '\n';
	std::cout << "rRot: " << GetRotationEuler(true).x << " / " << GetRotationEuler(true).y << " / " << GetRotationEuler(true).z << '\n';
	std::cout << "eRot: " << GetRotationEuler().x << " / " << GetRotationEuler().y << " / " << GetRotationEuler().z << '\n';
	std::cout << "scale: " << GetScale().x << " / " << GetScale().y << " / " << GetScale().z << '\n';
	std::cout << "shininess: " << shininess << '\n';
	std::cout << "---End Mesh Information---\n";
}

void Mesh::SetupBuffers()
{
	vao.Bind();
	vbo.BufferData(vertices);
	ebo.BufferData(indices);

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));

	glBindVertexArray(0);
}