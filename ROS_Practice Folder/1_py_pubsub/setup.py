from setuptools import find_packages, setup

package_name = 'py_pubsub'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,

    maintainer='isha',
    maintainer_email='isha@todo.todo',
    description='Examples of minimal publisher/subscriber using rclpy',
    license='Apache License 2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
             'talker1 = py_pubsub.publisher_memberfunction:main',
             'talker2 = py_pubsub.publisher_memberfunction2:main'
             'listener = py_pubsub.subscriber_memberfunction:main',
        ],
    },
)
