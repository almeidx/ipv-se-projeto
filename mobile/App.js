import React from "react";
import { View, Text, TouchableOpacity, StyleSheet } from "react-native";
import ArrowComponent from "./components/Arrow";

export default function App() {
  const handleArrowPress = async (req) => {
    await fetch("http://192.168.100.51/" + req);
  };

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Comando Carro</Text>

      <View style={styles.btnOutline}>
        <View style={styles.topAndBottom}>
          <ArrowComponent
            direction="Up"
            onPress={() => handleArrowPress("forward")}
          />
        </View>

        <View style={styles.middle}>
          <ArrowComponent
            direction="Left"
            onPress={() => handleArrowPress("left")}
          />
          <ArrowComponent
            direction="Right"
            onPress={() => handleArrowPress("right")}
          />
        </View>

        <View style={styles.topAndBottom}>
          <ArrowComponent
            direction="Down"
            onPress={() => handleArrowPress("backward")}
          />
        </View>
      </View>

      <View style={styles.btnContainer}>
        <TouchableOpacity
          style={styles.btn}
          onPress={() => handleArrowPress("increase")}
        >
          <Text style={styles.btnText}>+</Text>
        </TouchableOpacity>
        <TouchableOpacity
          style={styles.btn}
          onPress={() => handleArrowPress("decrease")}
        >
          <Text style={styles.btnText}>-</Text>
        </TouchableOpacity>
      </View>

      <TouchableOpacity
        style={styles.button}
        onPress={() => handleArrowPress("stop")}
      >
        <Text style={styles.btnText}>Stop</Text>
      </TouchableOpacity>

      <View style={styles.auto}>
        <TouchableOpacity
          style={styles.autoBtn}
          onPress={() => handleArrowPress("automatic")}
        >
          <Text style={styles.autoText}>Auto</Text>
        </TouchableOpacity>

        <TouchableOpacity
          style={styles.autoBtn}
          onPress={() => handleArrowPress("manual")}
        >
          <Text style={styles.autoText}>Manual</Text>
        </TouchableOpacity>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "center",
    alignItems: "center",
    width: "100%",
  },

  btnOutline: {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    backgroundColor: "#00000094",
    borderRadius: 300,
    width: 300,
    marginBottom: 20,
  },

  topAndBottom: {
    display: "flex",
    alignItems: "center",
    textAlign: "center",
    width: "100%",
    paddingVertical: 30,
  },

  middle: {
    display: "flex",
    flexDirection: "row",
    justifyContent: "center",
    gap: 130,
  },

  auto: {
    display: "flex",
    flexDirection: "row",
    justifyContent: "space-around",
    width: "100%",
    marginTop: 50,
  },

  autoBtn: {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    width: 100,
    height: 80,
    borderRadius: 50,
    backgroundColor: "gray",
  },

  autoText: {
    color: "white", // Example text color
    fontSize: 24,
    textAlign: "center",
    color: "white",
  },

  btnContainer: {
    display: "flex",
    flexDirection: "row",
    justifyContent: "space-between",
    width: "100%",
    paddingHorizontal: 25,
    gap: 10,
  },

  btn: {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    fontSize: 100,
    width: 80,
    height: 80,
    borderRadius: 50,
    backgroundColor: "gray",
  },

  btnText: {
    color: "white", // Example text color
    fontSize: 54,
    textAlign: "center",
    color: "white",
  },

  button: {
    display: "flex",
    marginTop: 50,
    width: "100%",
    backgroundColor: "#ff000094",
  },
  title: {
    paddingBottom: 50,
    textAlign: "center",
    fontSize: 40,
  },
});
