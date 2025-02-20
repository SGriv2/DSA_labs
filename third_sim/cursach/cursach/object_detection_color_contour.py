import cv2
import numpy as np

# Load the image
image = cv2.imread('fig.jpg')

# Convert the image to HSV color space
hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)

# Define color ranges for detection using a dictionary
color_ranges = {
    'red': ([0, 120, 70], [10, 255, 255]),
    'green': ([36, 25, 25], [86, 255, 255]),
    'blue': ([94, 80, 2], [126, 255, 255]),
    'yellow': ([20, 100, 100], [30, 255, 255]),
    'white': ([0, 0, 200], [180, 20, 255])
}

# Define colors for drawing contours and text
draw_colors = {
    'red': (0, 0, 255),
    'green': (0, 255, 0),
    'blue': (255, 0, 0),
    'yellow': (0, 255, 255),
    'white': (255, 255, 255)
}
# Iterate over each color range
for color_name, (lower, upper) in color_ranges.items():
    lower_color = np.array(lower)
    upper_color = np.array(upper)

    # Create a mask for the color
    mask = cv2.inRange(hsv, lower_color, upper_color)

    # Find contours in the mask
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    # Draw contours and labels on the original image
    for contour in contours:
        # Calculate the area of each contour
        area = cv2.contourArea(contour)
        if area > 500:  # Filter out small contours
            # Draw the contour on the image
            cv2.drawContours(image, [contour], -1, draw_colors[color_name], 3)

            # Get the contour's bounding box for placing text
            x, y, w, h = cv2.boundingRect(contour)
            cv2.putText(image, color_name, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, draw_colors[color_name], 2)
# Display the result
cv2.imshow('Detected Objects', image)
cv2.waitKey(0)
cv2.destroyAllWindows()

