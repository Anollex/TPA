import turtle

# Function to draw a Koch curve
def koch_curve(t, order, size):
    if order == 0:
        t.forward(size)
    else:
        for angle in [60, -120, 60, 0]:
            koch_curve(t, order-1, size/3)
            t.left(angle)

# Function to draw a snowflake
def snowflake(t, order, size):
    for _ in range(3):
        koch_curve(t, order, size)
        t.right(120)

# Main function
def main():
    # Setup
    screen = turtle.Screen()
    screen.setup(600, 600)
    screen.bgcolor("white")

    # Create turtle
    snowflake_turtle = turtle.Turtle()
    snowflake_turtle.speed(0)
    snowflake_turtle.color("blue")

    # Draw the snowflake
    snowflake(snowflake_turtle, 4, 300)

    # Hide turtle and display
    snowflake_turtle.hideturtle()
    turtle.done()

# Execute main function
if __name__ == "__main__":
    main()
