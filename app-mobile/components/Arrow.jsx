// components/ArrowComponent.js
import React from "react";
import { TouchableOpacity, Text } from "react-native";
import Icon from "react-native-vector-icons/FontAwesome"; // You can use other icon sets like Ionicons or MaterialIcons

const ArrowComponent = ({ direction, onPress }) => {
  const iconMap = {
    Up: "arrow-up",
    Down: "arrow-down",
    Left: "arrow-left",
    Right: "arrow-right",
  };

  const iconName = iconMap[direction] ?? "arrow-up"; // Default to arrow-up if direction is not recognized

  return (
    <TouchableOpacity
      onPress={onPress}
      style={{
        padding: 15,
        backgroundColor: "#7d7d7d94",
        backgroundColor: "gray",
        borderRadius: 100,
      }}
    >
      <Icon name={iconName} size={30} color="white" />
    </TouchableOpacity>
  );
};

export default ArrowComponent;
