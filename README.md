# Navigating-a-maze

 The rules are simple, you have to start at the top-left corner and find a path to the bottom-right corner; you can go left/right/up/down along the *s, ie. traverse horizontally, 
 vertically, but not diagonally along the routes. 
  The first operated similar to Hansel and Gretel's strategy of dropping breadcrumbs -- 
  keep dropping breadcrumbs along the route you take, if you hit a deadend then back trace the bread crumbs to the last point of intersection and take another route,if all routes
  from the last point of intersection have been taken then back trace the bread crumbs to the previous intersection. 
  If you end up back at the starting point, it means that no route exists. 
  If one does, then you will find it.

The same program can be rewritten easily to work on the graph as an input: graph.c.
