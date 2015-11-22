using UnityEngine;
using System.Collections;

using GamepadInput;

public class DualStickMovement : MonoBehaviour
{
    private Rigidbody rb;
    static int mIndice = 1;
    GamePad.Index numController;

    private float speed = 5.0f;
    private bool block = false;

    void setSpeed(float s)
    {
        speed = s;
    }

    void blockImput (bool op)
    {
        block = op;
    }


    void Start()
    {
        rb = GetComponent<Rigidbody>();
        numController = (GamePad.Index)mIndice;
        ++mIndice;
    }

    void FixedUpdate()
    {
        rb.velocity = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {   
        //Hacha
        if (Input.GetKeyDown(KeyCode.Space) || GamePad.GetButtonDown(GamePad.Button.B, numController)) {
            gameObject.SendMessage("useTool");
        }

        //Coger persona
        if (GamePad.GetButtonDown(GamePad.Button.A, numController)) {
            gameObject.SendMessage("pressAction");
        }


        //Movemos al personaje
        Vector3 leftStickAxis = (Vector3.right * GamePad.GetAxis(GamePad.Axis.LeftStick, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.LeftStick, numController).y);
        transform.position += leftStickAxis * speed * Time.deltaTime;

        //Orientamos al personaje
        Vector3 lookDir = (Vector3.right * GamePad.GetAxis(GamePad.Axis.RightStick, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.RightStick, numController).y);
        if (lookDir.sqrMagnitude > 0.0f) {
            transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);
            if (!block)
            {
                gameObject.BroadcastMessage("startShooting");
            } else {
                gameObject.BroadcastMessage("stopShooting");
            }
        } else {
            gameObject.BroadcastMessage("stopShooting");
        }
        
    }

}