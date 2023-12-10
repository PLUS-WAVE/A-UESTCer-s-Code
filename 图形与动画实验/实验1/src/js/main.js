import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { PCDLoader } from 'three/addons/loaders/PCDLoader.js';
import { GUI } from 'three/addons/libs/lil-gui.module.min.js';

const scene = new THREE.Scene();

const camera = new THREE.PerspectiveCamera(80, window.innerWidth / window.innerHeight, 0.01, 10000000);
camera.position.set(0, 0, 10);

const renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

const title1 = document.createElement('h4');
title1.textContent = 'PLUS-WAVE\'s PCD加载器';
title1.style.position = 'absolute';
title1.style.top = '1%';
title1.style.left = '42%';
title1.style.color = 'white';
document.body.appendChild(title1);

const title2 = document.createElement('h5');
title2.innerHTML = '点击右上角按钮选择文件<br>(看不见点云的话记得改改颜色或者缩放)';
title2.style.position = 'absolute';
title2.style.top = '4%';
title2.style.left = '41%';
title2.style.color = 'white';
title2.style.textAlign = 'center';
document.body.appendChild(title2);


const controls = new OrbitControls(camera, renderer.domElement);

const isRotation = { bool: false };

var gui = new GUI();
// gui.add(isRotation, 'bool').name('旋转');
var attributesFolder = gui.addFolder('点云设置');
gui.domElement.style.left = '0px';


function resetGUI() {
    // 删除之前的GUI
    gui.destroy();

    // 创建一个新的GUI实例
    gui = new GUI();
    // gui.add(isRotation, 'bool').name('旋转');
    attributesFolder = gui.addFolder('点云设置');
    gui.domElement.style.left = '0px';

}

var helpCamera = [];
for (let i = 0; i < 4; i++) {
    helpCamera[i] = new THREE.PerspectiveCamera(60, 1, 0.1, 0.4);
    scene.add(helpCamera[i]);
}


const transformMatrix0 = new THREE.Matrix4();
transformMatrix0.set(
    0.9635227966591445, -0.0298251417806896, -0.2659591721221557, -3.1861460134378618,
    0.04168012934974072, 0.9983679551673119, 0.03904091331448917, -0.0658694912288581,
    0.264360714054735, -0.04870202267670474, 0.963193400024973, 1.701830863209624117,
    0, 0, 0, 1
);
helpCamera[0].applyMatrix4(transformMatrix0);

const transformMatrix1 = new THREE.Matrix4();
transformMatrix1.set(
    0.8671344194352608, -0.01285630331924969, -0.4979082386300075, -1.981515886805006,
    0.03166906549661311, 0.9990671872561505, 0.02935686697614572, -0.0212592897059282,
    0.4970663626933977, -0.04122463842227529, 0.8667326925100427, 2.75149718348900723,
    0, 0, 0, 1
);
helpCamera[1].applyMatrix4(transformMatrix1);

const transformMatrix2 = new THREE.Matrix4();
transformMatrix2.set(
    0.7024094659673048, -0.007144654873624021, -0.711737238049452, -2.685856668225444,
    0.09031055886130245, 0.9927625554048429, 0.07916130079909767, -0.0514197827631538,
    0.7060204990492023, -0.1198810347502172, 0.6979710541487608, 2.332535510893329,
    0, 0, 0, 1
);
helpCamera[2].applyMatrix4(transformMatrix2);

const transformMatrix3 = new THREE.Matrix4();
transformMatrix3.set(
    0.5308375671028522, 0.00925889315102485, -0.8474230054995811, -3.381832006499801,
    0.1320681431688673, 0.9868199683489367, 0.09351125936341173, -0.0917595736102196,
    0.8371197542241209, -0.1615568722321077, 0.5226183063406084, 1.036010012067961,
    0, 0, 0, 1
);
helpCamera[3].applyMatrix4(transformMatrix3);


const helpers = [];
// 初始点云生成
const loader = new PCDLoader();
loader.load("./images/point_cloud.pcd", function (points) {
    points.geometry.center();
    points.geometry.rotateX(Math.PI);

    const material = new THREE.PointsMaterial({ color: 0xffffff, size: 0.08, vertexColors: true });
    //material.vertexColors = showVertices.bool;

    const pointCloud = new THREE.Points(points.geometry, material);
    scene.add(pointCloud);

    for (let i = 0; i < helpCamera.length; i++) {
        helpCamera[i].lookAt(pointCloud.position);
    }

    const folder = attributesFolder.addFolder(`点云 0`);

    const text = { pointsNum: points.geometry.attributes.position.count, file: "初始pcd" };
    folder.add(text, 'file').name('文件');
    folder.add(text, 'pointsNum').name('点数');

    folder.add(material, 'size', 0, 2).name('点大小');
    folder.addColor(material, 'color').name('点颜色');
    folder.add(material, 'vertexColors').name('显示顶点颜色').onChange(function () {
        material.needsUpdate = true; // 手动更新材质
    });

    for (let i = 0; i < 4; i++) {
        helpers[i] = new THREE.CameraHelper(helpCamera[i]);
        scene.add(helpers[i]);
    }
}
);



var count = 0;
const input = document.createElement('input');
const button = document.createElement('button');
button.textContent = '选择文件 (可选择多个)';
button.style.position = 'absolute';
button.style.top = '10px';
button.style.right = '10px';
button.onclick = function () {
    input.click();
};
document.body.appendChild(button);

input.type = 'file';
input.accept = '.pcd';
input.multiple = true;
input.style.display = 'none';
input.onchange = function (event) {
    count++;
    const files = event.target.files;
    const materials = [];
    const pointClouds = [];


    // 清除所有点云
    for (let i = 0; i < scene.children.length; i++) {
        const object = scene.children[i];
        scene.remove(object);
    }

    for (let i = 0; i < 4; i++) {
        scene.remove(helpers[i]);
    }

    for (let i = 0; i < files.length; i++) {
        const file = files[i];
        const reader = new FileReader();
        reader.readAsDataURL(file);
        reader.onload = function () {
            const data = reader.result;

            const loader = new PCDLoader();
            loader.load(data, function (points) {
                scene.remove(scene.children[0]);

                points.geometry.center();
                points.geometry.rotateX(Math.PI);

                var material = new THREE.PointsMaterial({ color: Math.random() * 0xffffff, size: 0.1, vertexColors: false });

                //material.vertexColors = showVertices.bool;
                materials.push(material);

                const pointCloud = new THREE.Points(points.geometry, material);
                pointClouds.push(pointCloud);

                if (pointClouds.length === files.length) {
                    // 所有点云数据都加载完成后，将它们添加到场景中
                    for (let j = 0; j < pointClouds.length; j++) {
                        scene.add(pointClouds[j]);
                    }

                    if (count >= 1) {
                        resetGUI();
                    }
                    gui.add(isRotation, 'bool').name('旋转');
                    // 为每个点云创建 GUI 控件
                    for (let j = 0; j < materials.length; j++) {
                        const material = materials[j];
                        const points = pointClouds[j];
                        const file = files[j];


                        const folder = attributesFolder.addFolder(`点云 ${j + 1}`);

                        const text = { pointsNum: points.geometry.attributes.position.count, file: file.name };
                        folder.add(text, 'file').name('文件');
                        folder.add(text, 'pointsNum').name('点数');

                        folder.add(material, 'size', 0, 2).name('点大小');
                        folder.addColor(material, 'color').name('点颜色');
                        folder.add(material, 'vertexColors').name('显示顶点颜色').onChange(function () {
                            material.needsUpdate = true; // 手动更新材质
                        });
                    }


                    // 计算点云的边界
                    const box = new THREE.Box3().setFromObject(scene);
                    // 计算点云的中心
                    const center = box.getCenter(new THREE.Vector3());
                    // 计算点云的大小
                    const size = box.getSize(new THREE.Vector3());

                    // 设置相机的位置为点云的中心，再向后移动一段距离
                    camera.position.copy(center);
                    camera.position.z += size.length();
                    camera.lookAt(center);

                }
            }
            );
        };
    }
};
document.body.appendChild(input);


// onresize 事件会在窗口被调整大小时发生
window.onresize = function () {
    // 重置渲染器输出画布，相机
    renderer.setSize(window.innerWidth, window.innerHeight);
    camera.aspect = window.innerWidth / window.innerHeight;
    camera.updateProjectionMatrix();
};



function animate() {
    if (isRotation.bool) {
        scene.rotation.y += 0.005;
    }

    renderer.render(scene, camera);

    requestAnimationFrame(animate);
}
animate();
