//import * as PCL from "pcl";
//import PointCloudViewer from "pcl.js/PointCloudViewer";
import * as PCL from "https://cdn.jsdelivr.net/npm/pcl.js@1.16.0/dist/pcl.esm.js";

import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { PCDLoader } from 'three/addons/loaders/PCDLoader.js';
import { GUI } from 'three/addons/libs/lil-gui.module.min.js';

const title2 = document.createElement('h3');
title2.innerHTML = '调整参数后需要切换显示模式';
title2.style.position = 'absolute';
title2.style.top = '660px   ';
title2.style.left = '1160px';
title2.style.color = 'white';
title2.style.textAlign = 'center';
document.body.appendChild(title2);

const container = document.getElementById('Panel2');
// 创建场景、相机、渲染器
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(80, container.offsetWidth / container.offsetHeight, 0.01, 10000000);
camera.position.set(0, 0, 3);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(container.offsetWidth, container.offsetHeight);
container.appendChild(renderer.domElement);
// 创建控制器
const controls = new OrbitControls(camera, renderer.domElement);

var gui = new GUI();
gui.title('示例2：点云关键点提取');
var attributesFolder = gui.addFolder('点云设置');
gui.domElement.style.left = '860px';
gui.domElement.style.position = 'absolute';

let cloudOriginalData;

var plcgui = new GUI();
plcgui.domElement.style.left = '860px';
plcgui.domElement.style.top = '198px';
plcgui.domElement.style.position = 'absolute';
const params = {
    SalientRadius: 6,
    NonMaxRadius: 4,
    Threshold21: 0.975,
    Threshold32: 0.975,
    MinNeighbors: 5,
};
plcgui.add(params, 'SalientRadius', 1, 10).name('SalientRadius').onChange(computeKeypoints);
plcgui.add(params, 'NonMaxRadius', 1, 10).name('NonMaxRadius').onChange(computeKeypoints);
plcgui.add(params, 'Threshold21', 0, 1).name('Threshold21').onChange(computeKeypoints);
plcgui.add(params, 'Threshold32', 0, 1).name('Threshold32').onChange(computeKeypoints);
plcgui.add(params, 'MinNeighbors', 0, 10).name('MinNeighbors').onChange(computeKeypoints);

let cloud;
let keypoints;

async function main() {
    const cloudBuffer = await fetch("./images/point_cloud.pcd").then((res) =>
        res.arrayBuffer()
    );

    await PCL.init({
        url: `https://cdn.jsdelivr.net/npm/pcl.js/dist/pcl-core.wasm`
    });

    cloud = PCL.loadPCDData(cloudBuffer, PCL.PointXYZ);
    // Get point cloud resolution
    const resolution = PCL.computeCloudResolution(cloud);
    const tree = new PCL.SearchKdTree();
    const iss = new PCL.ISSKeypoint3D();
    keypoints = new PCL.PointCloud();
    iss.setSearchMethod(tree);
    iss.setSalientRadius(6 * resolution);
    iss.setNonMaxRadius(4 * resolution);
    iss.setThreshold21(0.975);
    iss.setThreshold32(0.975);
    iss.setMinNeighbors(5);
    iss.setInputCloud(cloud);
    iss.compute(keypoints);

    cloudOriginalData = PCL.savePCDDataASCII(cloud);

    bindEvent();
}
async function computeKeypoints() {
    const cloudBuffer = await fetch("./images/point_cloud.pcd").then((res) =>
        res.arrayBuffer()
    );
    cloud = PCL.loadPCDData(cloudBuffer, PCL.PointXYZ);
    const resolution = PCL.computeCloudResolution(cloud);
    const tree = new PCL.SearchKdTree();
    const iss = new PCL.ISSKeypoint3D();
    keypoints = new PCL.PointCloud();
    iss.setSearchMethod(tree);
    iss.setSalientRadius(params.SalientRadius * resolution);
    iss.setNonMaxRadius(params.NonMaxRadius * resolution);
    iss.setThreshold21(params.Threshold21);
    iss.setThreshold32(params.Threshold32);
    iss.setMinNeighbors(params.MinNeighbors);
    iss.setInputCloud(cloud);
    iss.compute(keypoints);

}
function reset() {
    // 删除之前的GUI
    gui.destroy();

    // 创建一个新的GUI实例
    gui = new GUI();
    // gui.add(isRotation, 'bool').name('旋转');
    attributesFolder = gui.addFolder('点云设置');
    gui.domElement.style.left = '860px';
    gui.domElement.style.position = 'absolute';
    // 删除之前的点云
    while (scene.children.length > 0) {
        scene.remove(scene.children[0]);
    }
}

function bindEvent() {
    // 初始显示原始点云
    showPointCloud(false);
    const radioOriginal = document.getElementById("original2");
    const radioFiltered = document.getElementById("filtered2");

    [radioOriginal, radioFiltered].forEach((el) => {
        el.addEventListener("change", (e) => {
            const mode = e.target.id;
            reset()
            switch (mode) {
                case "original2":
                    showPointCloud(false);
                    break;
                case "filtered2":
                    showPointCloud(true);
                    break;
            }
        });
    });
}

function showPointCloud(showKeypoints) {

    // 将 ArrayBuffer 转换为字符串
    const decoder = new TextDecoder('utf-8');
    const pcdString = decoder.decode(new Uint8Array(cloudOriginalData));

    // 从字符串创建 Blob
    const blob = new Blob([pcdString], { type: 'text/plain' });

    // 从 Blob 创建 URL
    const url = URL.createObjectURL(blob);

    // 创建点云加载器
    const loader = new PCDLoader();
    // 加载点云模型
    loader.load(url, function (points) {

        const pos = [];
        if (showKeypoints) {
            for (let i = 0; i < keypoints.points.size; ++i) {
                const point = keypoints.points.get(i);
                pos.push(point.x, point.y, point.z);
            }
        }
        const geometry = new THREE.BufferGeometry();
        geometry.setAttribute('position', new THREE.Float32BufferAttribute(pos, 3));
        const keypointsMaterial = new THREE.PointsMaterial({ size: 0.05, color: 0xff0000 });
        const keypointsMesh = new THREE.Points(geometry, keypointsMaterial);

        // 创建点云材质
        const material = new THREE.PointsMaterial({ color: 0xffffff, size: 0.02, vertexColors: false });
        const pointCloud = new THREE.Points(points.geometry, material);


        const group = new THREE.Group();
        group.add(pointCloud);
        group.add(keypointsMesh);

        group.rotation.set(Math.PI, 0, 0);

        const boundingBox = new THREE.Box3();
        boundingBox.setFromObject(group);

        const center = new THREE.Vector3();
        boundingBox.getCenter(center);

        const translation = new THREE.Vector3();
        translation.subVectors(new THREE.Vector3(0, 0, 0), center);
        group.position.add(translation);

        scene.add(group);

        // 在 GUI 中添加点云相关设置
        const folder = attributesFolder.addFolder(`点云 0`);
        const text = { pointsNum: points.geometry.attributes.position.count, file: "初始pcd" };
        folder.add(text, 'file').name('文件');
        folder.add(text, 'pointsNum').name('点数');
        folder.add(material, 'size', 0.001, 0.03).name('点大小');
        folder.addColor(material, 'color').name('点颜色');
        folder.add(keypointsMaterial, 'size', 0.03, 0.1).name('关键点大小');
        //camera.lookAt(group);
    });

}

// // onresize 事件会在窗口被调整大小时发生
// window.onresize = function () {
//     // 重置渲染器输出画布，相机
//     renderer.setSize(container.offsetWidth, container.offsetHeight);
//     camera.aspect = container.offsetWidth / container.offsetHeight;
//     camera.updateProjectionMatrix();
// };

// 渲染循环
function animate() {
    requestAnimationFrame(animate);

    // 渲染场景
    renderer.render(scene, camera);
}

main();
// 调用渲染循环
animate();




