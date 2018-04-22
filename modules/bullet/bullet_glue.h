
#ifndef BB_BULLET_H
#define BB_BULLET_H

#include "btBulletDynamicsCommon.h"

namespace bbBullet{

	btVector3 calculateLocalInertia( btCollisionShape *self,btScalar mass );
	
	btTransform getWorldTransform( btMotionState *self );
	
	struct Point2PointConstraint : public btPoint2PointConstraint{
		
		Point2PointConstraint(btRigidBody* rbA,btRigidBody* rbB, const btVector3& pivotInA,const btVector3& pivotInB):
		btPoint2PointConstraint(*rbA,*rbB,pivotInA,pivotInB){}

		Point2PointConstraint(btRigidBody* rbA,const btVector3& pivotInA):
		btPoint2PointConstraint(*rbA,pivotInA){}
	};
	
	struct MotionState : public btMotionState{
		
		virtual void setWorldTransform( btTransform *worldTrans ){
		}

		virtual void getWorldTransform( btTransform *worldTrans ){
		}

		virtual void setWorldTransform( const btTransform &worldTrans ){
			
			this->setWorldTransform( const_cast<btTransform*>( &worldTrans ) );
		}
				
		virtual void getWorldTransform( btTransform &worldTrans )const{
			
			const_cast<MotionState*>( this )->getWorldTransform( &worldTrans );
		}
	};
	
	struct DefaultMotionState : public btDefaultMotionState{

		DefaultMotionState(){
		}
		
 		DefaultMotionState( const btTransform &startTrans,const btTransform &centerOfMassOffset ):btDefaultMotionState( startTrans,centerOfMassOffset ){
 		}

		void setWorldTransform( btTransform *worldTrans ){
		
			btDefaultMotionState::setWorldTransform( *worldTrans );
		}

		void getWorldTransform( btTransform *worldTrans ){

			btDefaultMotionState::getWorldTransform( *worldTrans );
		}
	};
	
	void rayTest( btCollisionWorld *self,
		const btVector3 &rayFromWorld,
		const btVector3 &rayToWorld,
		btCollisionWorld::RayResultCallback *result );

	void convexSweepTest( btCollisionWorld *self,
		const btConvexShape *castShape,
		const btTransform &castFrom,
		const btTransform &castTo,
		btCollisionWorld::ConvexResultCallback *result,
		btScalar allowedCcdPenetration );
}

#endif
