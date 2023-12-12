import { setTimeout } from "node:timers/promises";

await fetch("http://192.168.100.51:80/forward");
await setTimeout(1000);
await fetch("http://192.168.100.51:80/backward");
await setTimeout(1000);
await fetch("http://192.168.100.51:80/forward");
await setTimeout(1000);
await fetch("http://192.168.100.51:80/backward");
await setTimeout(1000);
await fetch("http://192.168.100.51:80/forward");
await setTimeout(1000);
await fetch("http://192.168.100.51:80/backward");
await setTimeout(1000);

await fetch("http://192.168.100.51:80/stop");
