//import * as PCL from "pcl";
//import PointCloudViewer from "pcl.js/PointCloudViewer";
import * as PCL from "https://cdn.jsdelivr.net/npm/pcl.js@1.16.0/dist/pcl.esm.js";
import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { PCDLoader } from 'three/addons/loaders/PCDLoader.js';
import { GUI } from 'three/addons/libs/lil-gui.module.min.js';

const container = document.getElementById('Panel1');
// 创建场景、相机、渲染器
const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(80, container.offsetWidth / container.offsetHeight, 0.01, 10000000);
camera.position.set(0, 0, 1.5);
const renderer = new THREE.WebGLRenderer();
renderer.setSize(container.offsetWidth, container.offsetHeight);
container.appendChild(renderer.domElement);
// 创建控制器
const controls = new OrbitControls(camera, renderer.domElement);

var gui = new GUI();
gui.title('示例1：点云过滤');
var attributesFolder = gui.addFolder('点云设置');
gui.domElement.style.left = '0.1%';
gui.domElement.style.position = 'absolute';

let cloudOriginalData;
let cloudFilteredData;

var plcgui = new GUI();
plcgui.domElement.style.left = '0.1%';
plcgui.domElement.style.top = '175px';
plcgui.domElement.style.position = 'absolute';

const params = {
    meanK: 40,
    stddevMulThresh: 3.0
};
plcgui.add(params, 'meanK', 1, 100).name('meanK').onChange(filterPointCloud);
plcgui.add(params, 'stddevMulThresh', 0.1, 10).name('stddevMulThresh').onChange(filterPointCloud);

let cloud;

async function main() {
    const cloudBuffer = await fetch("./images/point_cloud.pcd").then((res) =>
        res.arrayBuffer()
    );

    await PCL.init({
        url: `https://cdn.jsdelivr.net/npm/pcl.js/dist/pcl-core.wasm`
    });

    cloud = PCL.loadPCDData(cloudBuffer, PCL.PointXYZ);


    const sor = new PCL.StatisticalOutlierRemoval();
    sor.setInputCloud(cloud);
    sor.setMeanK(40);
    sor.setStddevMulThresh(3.0);
    const cloudFiltered = sor.filter();

    cloudFilteredData = PCL.savePCDDataASCII(cloudFiltered);
    cloudOriginalData = PCL.savePCDDataASCII(cloud);

    bindEvent();
}

async function filterPointCloud() {
    const cloudBuffer = await fetch("./images/point_cloud.pcd").then((res) =>
        res.arrayBuffer()
    );
    cloud = PCL.loadPCDData(cloudBuffer, PCL.PointXYZ);
    const sor = new PCL.StatisticalOutlierRemoval();
    sor.setInputCloud(cloud);
    sor.setMeanK(params.meanK);
    sor.setStddevMulThresh(params.stddevMulThresh);
    const cloudFiltered = sor.filter();

    cloudFilteredData = PCL.savePCDDataASCII(cloudFiltered);
    cloudOriginalData = PCL.savePCDDataASCII(cloud);
}
function reset() {
    // 删除之前的GUI
    gui.destroy();

    // 创建一个新的GUI实例
    gui = new GUI();
    // gui.add(isRotation, 'bool').name('旋转');
    gui.title('点云过滤');
    attributesFolder = gui.addFolder('点云设置');
    gui.domElement.style.left = '0.1%';
    gui.domElement.style.position = 'absolute';
    // 删除之前的点云
    scene.remove(scene.children[0]);

}

function bindEvent() {
    // 初始显示原始点云
    showPointCloud(cloudOriginalData);
    const radioOriginal = document.getElementById("original1");
    const radioFiltered = document.getElementById("filtered1");

    [radioOriginal, radioFiltered].forEach((el) => {
        el.addEventListener("change", (e) => {
            const mode = e.target.id;
            reset()
            switch (mode) {
                case "original1":
                    showPointCloud(cloudOriginalData);
                    break;
                case "filtered1":
                    showPointCloud(cloudFilteredData);
                    break;
            }
        });
    });
}

function showPointCloud(currentPointCloud) {

    // 将 ArrayBuffer 转换为字符串
    const decoder = new TextDecoder('utf-8');
    const pcdString = decoder.decode(new Uint8Array(currentPointCloud));

    // 从字符串创建 Blob
    const blob = new Blob([pcdString], { type: 'text/plain' });

    // 从 Blob 创建 URL
    const url = URL.createObjectURL(blob);

    // 创建点云加载器
    const loader = new PCDLoader();
    // 加载点云模型
    loader.load(url, function (points) {
        // 将点云几何居中
        points.geometry.center();
        points.geometry.rotateX(Math.PI);
        // 创建点云材质
        const material = new THREE.PointsMaterial({ color: 0xffffff, size: 0.02, vertexColors: false });

        if (currentPointCloud == cloudOriginalData) {
            material.color.setHex(0xad1010);
        } else {
            material.color.setHex(0x1ea10c);
        }
        // 创建点云对象
        const pointCloud = new THREE.Points(points.geometry, material);
        scene.add(pointCloud);

        // 在 GUI 中添加点云相关设置
        const folder = attributesFolder.addFolder(`点云 0`);
        const text = { pointsNum: points.geometry.attributes.position.count, file: "初始pcd" };
        folder.add(text, 'file').name('文件');
        folder.add(text, 'pointsNum').name('点数');
        folder.add(material, 'size', 0.001, 0.03).name('点大小');
        folder.addColor(material, 'color').name('点颜色');
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




