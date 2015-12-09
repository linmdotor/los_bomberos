using UnityEngine;
using System.Collections;

using GamepadInput;

public class DualStickMovement : MonoBehaviour
{
    private Rigidbody rb;
    static int mIndice = 1;
    public GamePad.Index numController;

    private float speed = 5.0f;
    private bool block = false;
    private bool m_blockShoot = false;

    void setSpeed(float s)
    {
        speed = s;
    }

    void blockImput (bool op)
    {
        block = op;
    }
    public void blockShoot(bool op)
    {
        m_blockShoot = op;
    }
    void Awake()
    {
        rb = GetComponent<Rigidbody>();
        numController = (GamePad.Index)mIndice;
        ++mIndice;
    }
    void Start()
    {
        
    }

    void FixedUpdate()
    {
        rb.velocity = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {   
        //Hacha
        if (GamePad.GetButtonDown(GamePad.Button.B, numController)) {
            gameObject.SendMessage("useTool");
        }

        //Coger persona
        if (GamePad.GetButtonDown(GamePad.Button.A, numController)) {
            gameObject.SendMessage("pressAction");
        }

        //Enviar mensaje 1
        if (GamePad.GetButtonDown(GamePad.Button.Y, numController))
        {
            gameObject.SendMessage("helpMessage", Character.HELP_MESSAGES.HELP_MESSAGES_FIRE_HERE);
        }
        //Enviar mensaje 2
        if (GamePad.GetButtonDown(GamePad.Button.X, numController))
        {
            gameObject.SendMessage("helpMessage", Character.HELP_MESSAGES.HELP_MESSAGES_NPC_HERE);
        }

        //Movemos al personaje
        Vector3 leftStickAxis = (Vector3.right * GamePad.GetAxis(GamePad.Axis.LeftStick, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.LeftStick, numController).y);
        Vector3 aux = Vector3.zero;
        if (leftStickAxis.magnitude < 0.01f)
        {
            aux = (Vector3.right * GamePad.GetAxis(GamePad.Axis.KeyboardL, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.KeyboardL, numController).y);
            if (aux.magnitude > 0.0f)
            {
                leftStickAxis = aux;
            }
        }

        transform.position += leftStickAxis * speed * Time.deltaTime;

        //llama a isMoving o IsNotMoving para reproducir el sonido de las pisadas
        if (leftStickAxis.x == 0 && leftStickAxis.y == 0)
        {
            gameObject.BroadcastMessage("isNotMoving");
        }
        else
        {
            gameObject.BroadcastMessage("isMoving");
        }

        //Orientamos al personaje
        Vector3 lookDir = (Vector3.right * GamePad.GetAxis(GamePad.Axis.RightStick, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.RightStick, numController).y);
        if (!m_blockShoot && lookDir.sqrMagnitude > 0.0f)
        {
            transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);
            if (!block)
            {
                gameObject.BroadcastMessage("startShooting");
            } else {
                gameObject.BroadcastMessage("stopShooting");
            }
        } else {
            lookDir = (Vector3.right * GamePad.GetAxis(GamePad.Axis.KeyboardR, numController).x + Vector3.forward * GamePad.GetAxis(GamePad.Axis.KeyboardR, numController).y);
            if (!m_blockShoot && lookDir.sqrMagnitude > 0.0f)
            {
                transform.rotation = Quaternion.LookRotation(lookDir, Vector3.up);
                if (!block)
                {
                    gameObject.BroadcastMessage("startShooting");
                }
                else
                {
                    gameObject.BroadcastMessage("stopShooting");
                }
            }
            else
            {
                gameObject.BroadcastMessage("stopShooting");
            }
        }
        
    }

}