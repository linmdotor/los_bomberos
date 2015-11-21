using UnityEngine;
using System.Collections;

public class GameEvent {
	
	public EventManager.EVENTS										type;
	public float 													fTime;	
	public void SendEvent()
	{
		fTime = Time.time;
		EventManager.newEvent( this );
	}
}
public class EventFirefighterOnFire : GameEvent {
	public Character						 			m_firefighter;
    public EventFirefighterOnFire() { type = EventManager.EVENTS.EVENT_FIREFIGHTER_ON_FIRE; }	
}