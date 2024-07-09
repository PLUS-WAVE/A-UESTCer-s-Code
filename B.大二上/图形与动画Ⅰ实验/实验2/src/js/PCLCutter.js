//import * as PCL from "pcl";
//import PointCloudViewer from "pcl.js/PointCloudViewer";
import * as PCL from "https://cdn.jsdelivr.net/npm/pcl.js@1.16.0/dist/pcl.esm.js";
import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { PCDLoader } from 'three/addons/loaders/PCDLoader.js';
import { GUI } from 'three/addons/libs/lil-gui.module.min.js';

const container = document.getElementById('Panel3');
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
gui.title('示例3：最小切割');
var attributesFolder = gui.addFolder('点云设置');
gui.domElement.style.left = '0.1%';
gui.domElement.style.top = '407px';
gui.domElement.style.position = 'absolute';

let cloudOriginalData;
let cloudFilteredData;

var plcgui = new GUI();
plcgui.domElement.style.left = '0.1%';
plcgui.domElement.style.top = '582px';
plcgui.domElement.style.position = 'absolute';

const params = {
    Radius: 3.0433856,
    Sigma: 0.1,
    SourceWeight: 0.8,
    NumberOfNeighbours: 14
};
plcgui.add(params, 'Radius', 0.100, 10).name('Radius').onChange(filterPointCloud);
plcgui.add(params, 'Sigma', 0.05, 0.3).name('Sigma').onChange(filterPointCloud);
plcgui.add(params, 'SourceWeight', 0.001, 1).name('SourceWeight').onChange(filterPointCloud);
plcgui.add(params, 'NumberOfNeighbours', 1, 50).name('NumberOfNeighbours').onChange(filterPointCloud);

let cloud;

async function main() {
    const cloudBuffer = await fetch("./images/point_cloud.pcd").then((res) =>
        res.arrayBuffer()
    );

    await PCL.init({
        url: `https://cdn.jsdelivr.net/npm/pcl.js/dist/pcl-core.wasm`
    });

    cloud = PCL.loadPCDData(cloudBuffer, PCL.PointXYZ);

    const objectCenter = new PCL.PointXYZ(2, 0, 0);
    const foregroundPoints = new PCL.PointCloud();
    foregroundPoints.addPoint(objectCenter);

    const seg = new PCL.MinCutSegmentation();
    seg.setForegroundPoints(foregroundPoints);
    seg.setInputCloud(cloud);
    seg.setRadius(3.0433856);
    seg.setSigma(0.1);
    seg.setSourceWeight(0.8);
    seg.setNumberOfNeighbours(14);
    seg.extract();
    const coloredCloud = seg.getColoredCloud();

    cloudFilteredData = PCL.savePCDDataASCII(coloredCloud);
    cloudOriginalData = PCL.savePCDDataASCII(cloud);

    bindEvent();
}

async function filterPointCloud() {
    const cloudBuffer = await fetch("./images/point_cloud.pcd").then((res) =>
        res.arrayBuffer()
    );
    cloud = PCL.loadPCDData(cloudBuffer, PCL.PointXYZ);
    const objectCenter = new PCL.PointXYZ(2, 0, 0);
    const foregroundPoints = new PCL.PointCloud();
    foregroundPoints.addPoint(objectCenter);

    const seg = new PCL.MinCutSegmentation();
    seg.setForegroundPoints(foregroundPoints);
    seg.setInputCloud(cloud);
    seg.setRadius(params.Radius);
    seg.setSigma(params.Sigma);
    seg.setSourceWeight(params.SourceWeight);
    seg.setNumberOfNeighbours(params.NumberOfNeighbours);
    seg.extract();
    const coloredCloud = seg.getColoredCloud();

    cloudFilteredData = PCL.savePCDDataASCII(coloredCloud);
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
    gui.domElement.style.top = '407px';
    gui.domElement.style.position = 'absolute';
    // 删除之前的点云
    scene.remove(scene.children[0]);

}

function bindEvent() {
    // 初始显示原始点云
    showPointCloud(cloudOriginalData);
    const radioOriginal = document.getElementById("original3");
    const radioFiltered = document.getElementById("filtered3");

    [radioOriginal, radioFiltered].forEach((el) => {
        el.addEventListener("change", (e) => {
            const mode = e.target.id;
            reset()
            switch (mode) {
                case "original3":
                    showPointCloud(cloudOriginalData);
                    break;
                case "filtered3":
                    showPointCloud(cloudFilteredData);
                    break;
            }
        });
    });
}

function showPointCloud(currentPointCloud) {

    // 将 ArrayBuffer 转换为字符串
    const decoder = new TextDecoder('utf-8');
    const pcdString = decoder.decode(new Uint8Array(cloudFilteredData));

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

        let showVertColor = false;
        if (currentPointCloud != cloudOriginalData) {
            showVertColor = true;
        }

        // 创建点云材质
        const material = new THREE.PointsMaterial({ color: 0xffffff, size: 0.02, vertexColors: showVertColor });

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




