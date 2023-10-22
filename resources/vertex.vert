#version 400
        layout(location=0) in vec3 vp;
        layout(location=1) in vec3 vertex_normal;
        uniform mat4 modelMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 projectionMatrix;
        out vec3 vs_normal;
        void main () {
            gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (vp, 1.0);
            vs_normal = vertex_normal;
        }