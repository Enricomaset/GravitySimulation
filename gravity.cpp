#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>
#include <vector>

constexpr double G = 1.0;
constexpr double DT = 0.001;
constexpr double SOFTENING = 0.01;

constexpr double PI = 3.14159265358979323846;

// Corpo gravitazionale
struct Body {
    double x;
    double y;

    double vx;
    double vy;

    double ax;
    double ay;

    double mass;

    float red;
    float green;
    float blue;
};

// Inizializza i corpi
void initialize_bodies(
    std::vector<Body>& bodies
) {
    bodies.push_back({
        -0.75,
        0.25,
        0.5,
        0.4,
        0.0,
        0.0,
        1.0,
        1.0f,
        0.0f,
        0.0f
    });

    bodies.push_back({
        1.0,
        -0.25,
        0.5,
        0.4,
        0.0,
        0.0,
        1.0,
        0.0f,
        1.0f,
        0.0f
    });

    bodies.push_back({
        0.0,
        0.0,
        -1.0,
        -0.85,
        0.0,
        0.0,
        1.0,
        0.0f,
        0.0f,
        1.0f
    });
}

// Calcola le accelerazioni gravitazionali
void compute_accelerations(
    std::vector<Body>& bodies
) {
    const int N =
        static_cast<int>(bodies.size());

    // Azzera le accelerazioni
    for (int i = 0; i < N; ++i) {
        bodies[i].ax = 0.0;
        bodies[i].ay = 0.0;
    }

    // Calcola l'effetto di ogni corpo j sul corpo i
    for (int i = 0; i < N; ++i) {

        for (int j = 0; j < N; ++j) {

            if (i == j) {
                continue;
            }

            const double dx =
                bodies[j].x - bodies[i].x;

            const double dy =
                bodies[j].y - bodies[i].y;

            const double distance_squared =
                dx * dx
                + dy * dy
                + SOFTENING * SOFTENING;

            const double distance =
                std::sqrt(distance_squared);

            const double distance_cubed =
                distance_squared * distance;

            bodies[i].ax += G * bodies[j].mass * dx / distance_cubed;

            bodies[i].ay += G * bodies[j].mass * dy / distance_cubed;
        }
    }
}

// Esegue un passo temporale
void step(
    std::vector<Body>& bodies
) {
    compute_accelerations(bodies);

    for (Body& body : bodies) {

        // Aggiorna la velocità
        body.vx += body.ax * DT;
        body.vy += body.ay * DT;

        // Aggiorna la posizione
        body.x += body.vx * DT;
        body.y += body.vy * DT;
    }
}

// Disegna un cerchio
void draw_circle(
    float center_x,
    float center_y,
    float radius,
    float red,
    float green,
    float blue
) {
    constexpr int segments = 40;

    glColor3f(
        red,
        green,
        blue
    );

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(
        center_x,
        center_y
    );

    for (int i = 0; i <= segments; ++i) {

        const double angle =
            2.0
            * PI
            * static_cast<double>(i)
            / static_cast<double>(segments);

        const float x =
            center_x
            + radius
            * static_cast<float>(
                std::cos(angle)
            );

        const float y =
            center_y
            + radius
            * static_cast<float>(
                std::sin(angle)
            );

        glVertex2f(x, y);
    }

    glEnd();
}

// Disegna tutti i corpi
void draw_bodies(
    const std::vector<Body>& bodies
) {
    constexpr float radius = 0.025f;

    for (const Body& body : bodies) {

        draw_circle(
            static_cast<float>(body.x),
            static_cast<float>(body.y),
            radius,
            body.red,
            body.green,
            body.blue
        );
    }
}

int main() {

    std::vector<Body> bodies;

    initialize_bodies(bodies);

    if (!glfwInit()) {
        std::cerr
            << "Errore durante l'inizializzazione "
            << "di GLFW\n";

        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(
        800,
        800,
        "N-Body gravitational simulation",
        nullptr,
        nullptr
    );

    if (window == nullptr) {
        std::cerr
            << "Impossibile creare la finestra\n";

        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(window)) {

        if (
            glfwGetKey(
                window,
                GLFW_KEY_ESCAPE
            )
            == GLFW_PRESS
        ) {
            glfwSetWindowShouldClose(
                window,
                GLFW_TRUE
            );
        }

        // Più step fisici per ogni frame grafico
        for (int i = 0; i < 5; ++i) {
            step(bodies);
        }

        int width;
        int height;

        glfwGetFramebufferSize(
            window,
            &width,
            &height
        );

        glViewport(
            0,
            0,
            width,
            height
        );

        glClearColor(
            0.05f,
            0.05f,
            0.05f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        draw_bodies(bodies);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
