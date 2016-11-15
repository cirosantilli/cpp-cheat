# Concepts

-   acceleration: continuous speed change, ignores mass
-   force: continuous speed change, considers mass
-   impulse: instantaneous speed change, considers mass
-   velocity change: instantaneous speed change, ignores mass
-   rag doll physics: https://www.youtube.com/watch?v=XKuleYcVF-U
    - https://en.wikipedia.org/wiki/Ragdoll_physics
    - http://www.havok.com/physics/
    I distinctly remember sing that on a CS:GO game in 2016-04-15, when a dead body fell from a platform
-   AABB axis-aligned bounding-box http://www.gamasutra.com/view/feature/131833/when_two_hearts_collide_.php
-   btRigidBody , the key classdocuments that there are 3 types of bodies:
    - Dynamic rigid bodies, with positive mass. Motion is controlled by rigid body dynamics.
    - Fixed objects with zero mass. They are not moving (basically collision objects)
    - Kinematic objects, which are objects without mass, but the user can move them. There is on-way interaction, and Bullet calculates a velocity based on the timestep and previous and current world transform.
-   sleeping object: TODO
-   island split algorithm?
-   collision primitives: <http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Shapes>
    - A few efficient geometric ones + more general meshes of points.
-   collision detection:
    - http://gamedev.stackexchange.com/questions/34198/when-to-use-collision-detection-methods
    - Unity discrete, continuous and Continuous Dynamic demo https://www.youtube.com/watch?v=6qKiSjaJzfo
