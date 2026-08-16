//
// Created by ricka on 8/1/26.
//

#include <noi_engine/core/model/mesh.hpp>
#include <utility>
#include "../glad/glad.h"

noi_engine::mesh::mesh(std::vector<vertex> vertices, std::vector<uint32_t> indices)
	: m_vertices(std::move(vertices)), m_indices(std::move(indices))
{
	this->upload();
}

noi_engine::mesh::~mesh()
{
	if (m_vao != 0)
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
	}
}

noi_engine::mesh::mesh(mesh&& other) noexcept
	: m_vertices(std::move(other.m_vertices)),
	  m_indices(std::move(other.m_indices)),
	  m_vao(other.m_vao),
	  m_vbo(other.m_vbo),
	  m_ebo(other.m_ebo)
{
	other.m_vao = 0;
	other.m_vbo = 0;
	other.m_ebo = 0;
}

auto noi_engine::mesh::operator=(mesh&& other) noexcept -> mesh&
{
	if (this == &other)
		return *this;

	m_vertices = std::move(other.m_vertices);
	m_indices = std::move(other.m_indices);
	m_vao = other.m_vao;
	m_vbo = other.m_vbo;
	m_ebo = other.m_ebo;

	other.m_vao = 0;
	other.m_vbo = 0;
	other.m_ebo = 0;

	return *this;
}

auto noi_engine::mesh::upload() -> void
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	this->bind();

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,
	             static_cast<GLsizeiptr>(m_vertices.size() * sizeof(vertex)),
	             m_vertices.data(),
	             GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	             static_cast<GLsizeiptr>(m_indices.size() * sizeof(uint32_t)),
	             m_indices.data(),
	             GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
	                       reinterpret_cast<void*>(offsetof(vertex, position))); // NOLINT(*-no-int-to-ptr)
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex),
	                       reinterpret_cast<void*>(offsetof(vertex, normal))); // NOLINT(*-no-int-to-ptr)
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex),
	                       reinterpret_cast<void*>(offsetof(vertex, uv))); // NOLINT(*-no-int-to-ptr)
	glEnableVertexAttribArray(2);

	this->unbind();
}

auto noi_engine::mesh::bind() const -> void
{
	glBindVertexArray(m_vao);
}

auto noi_engine::mesh::unbind() const -> void
{
	glBindVertexArray(0);
}

auto noi_engine::mesh::vao() const noexcept -> uint32_t
{
	return m_vao;
}

auto noi_engine::mesh::index_count() const noexcept -> uint32_t
{
	return static_cast<uint32_t>(m_indices.size());
}